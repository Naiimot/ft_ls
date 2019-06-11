#include "acl.h"
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <mach/mach.h>
#include "membership.h"
#include <servers/bootstrap.h>
#include <libkern/OSByteOrder.h>
#ifdef DS_AVAILABLE
#include <xpc/xpc.h>
#include <xpc/private.h>
#include <opendirectory/odipc.h>
#include <pthread.h>
#include <mach-o/dyld_priv.h>
#endif
static const uuid_t _user_compat_prefix = {0xff, 0xff, 0xee, 0xee, 0xdd, 0xdd, 0xcc, 0xcc, 0xbb, 0xbb, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00};
static const uuid_t _group_compat_prefix = {0xab, 0xcd, 0xef, 0xab, 0xcd, 0xef, 0xab, 0xcd, 0xef, 0xab, 0xcd, 0xef, 0x00, 0x00, 0x00, 0x00};

#define COMPAT_PREFIX_LEN	(sizeof(uuid_t) - sizeof(id_t))

#define MBR_REC_TYPE_USER 1
#define MBR_REC_TYPE_GROUP 2

	static bool
_mbr_od_available(void)
{
#if DS_AVAILABLE
	xpc_pipe_t pipe = _mbr_xpc_pipe(false);
	if (pipe != NULL) {
		xpc_release(pipe);
		return true;
	}
#endif
	return false;
}

int
ft_identifier_translate(int id_type, const void *identifier, size_t identifier_size, int target_type, void **result, int *rec_type)
{
#if DS_AVAILABLE
	xpc_object_t payload, reply;
#endif
	id_t tempID;
	size_t identifier_len;
	int rc = EIO;

	if (identifier == NULL || result == NULL || identifier_size == 0) return EIO;

	if (identifier_size == (size_t)-1) {
		identifier_size = ft_strlen(identifier);
	} else {
		/* 10898647: For types that are known to be strings, send the smallest necessary amount of data. */
		switch (id_type) {
		case ID_TYPE_USERNAME:
		case ID_TYPE_GROUPNAME:
		case ID_TYPE_GROUP_NFS:
		case ID_TYPE_USER_NFS:
		case ID_TYPE_X509_DN:
		case ID_TYPE_KERBEROS:
		case ID_TYPE_NAME:
			identifier_len = strlen(identifier);
			if (identifier_size > identifier_len) {
				identifier_size = identifier_len;
			}
			break;
		}
	}

	switch (target_type) {
		case ID_TYPE_GID:
		case ID_TYPE_UID:
		case ID_TYPE_UID_OR_GID:
			/* shortcut UUIDs using compatibilty prefixes */
			if (id_type == ID_TYPE_UUID) {
				const uint8_t *uu = identifier;

				if (identifier_size != sizeof(uuid_t)) return EINVAL;

				if (ft_memcmp(uu, _user_compat_prefix, COMPAT_PREFIX_LEN) == 0) {
					id_t *tempRes = malloc(sizeof(*tempRes));
					if (tempRes == NULL) return ENOMEM;
					ft_memcpy(&tempID, &uu[COMPAT_PREFIX_LEN], sizeof(tempID));
					(*tempRes) = ntohl(tempID);
					(*result) = tempRes;
					if (rec_type != NULL) {
						(*rec_type) = MBR_REC_TYPE_USER;
					}
					return 0;
				} else if (ft_memcmp(uu, _group_compat_prefix, COMPAT_PREFIX_LEN) == 0) {
					id_t *tempRes = malloc(sizeof(*tempRes));
					if (tempRes == NULL) return ENOMEM;
					ft_memcpy(&tempID, &uu[COMPAT_PREFIX_LEN], sizeof(tempID));
					(*tempRes) = ntohl(tempID);
					(*result) = tempRes;
					if (rec_type != NULL) {
						(*rec_type) = MBR_REC_TYPE_GROUP;
					}
					return 0;
				}
			}
			break;

		case ID_TYPE_UUID:
			/* if this is a UID or GID translation, we shortcut UID/GID 0 */
			/* or if no OD, we return compatibility UUIDs */
			switch (id_type) {
				case ID_TYPE_UID:
					if (identifier_size != sizeof(tempID)) return EINVAL;

					tempID = *((id_t *) identifier);
					if ((tempID == 0) || (_mbr_od_available() == FALSE)) {
						uint8_t *tempUU = malloc(sizeof(uuid_t));
						if (tempUU == NULL) return ENOMEM;
						uuid_copy(tempUU, _user_compat_prefix);
						*((id_t *) &tempUU[COMPAT_PREFIX_LEN]) = htonl(tempID);
						(*result) = tempUU;
						if (rec_type != NULL) {
							(*rec_type) = MBR_REC_TYPE_USER;
						}
						return 0;
					}
					break;

				case ID_TYPE_GID:
					if (identifier_size != sizeof(tempID)) return EINVAL;

					tempID = *((id_t *) identifier);
					if ((tempID == 0) || (_mbr_od_available() == FALSE)) {
						uint8_t *tempUU = malloc(sizeof(uuid_t));
						if (tempUU == NULL) return ENOMEM;
						uuid_copy(tempUU, _group_compat_prefix);
						*((id_t *) &tempUU[COMPAT_PREFIX_LEN]) = htonl(tempID);
						(*result) = tempUU;
						if (rec_type != NULL) {
							(*rec_type) = MBR_REC_TYPE_GROUP;
						}
						return 0;
					}
					break;
			}
			break;
	}


#if DS_AVAILABLE
	payload = xpc_dictionary_create(NULL, NULL, 0);
	if (payload == NULL) return EIO;

	xpc_dictionary_set_int64(payload, "requesting", target_type);
	xpc_dictionary_set_int64(payload, "type", id_type);
	xpc_dictionary_set_data(payload, "identifier", identifier, identifier_size);

	reply = _od_rpc_call("mbr_identifier_translate", payload, _mbr_xpc_pipe);
	if (reply != NULL) {
		const void *reply_id;
		size_t idLen;

		rc = (int) xpc_dictionary_get_int64(reply, "error");
		if (rc == 0) {
			reply_id = xpc_dictionary_get_data(reply, "identifier", &idLen);
			if (reply_id != NULL) {
				char *identifier = malloc(idLen);
				if (identifier == NULL) return ENOMEM;

				memcpy(identifier, reply_id, idLen); // should already be NULL terminated, etc.
				(*result) = identifier;

				if (rec_type != NULL) {
					(*rec_type) = (int) xpc_dictionary_get_int64(reply, "rectype");
				}
			} else {
				(*result) = NULL;
				rc = ENOENT;
			}
		}

		xpc_release(reply);
	}

	xpc_release(payload);
#endif

	return rc;
}

int
ft_uuid_to_id(const uuid_t uu, uid_t *id, int *id_type)
{
	id_t *result;
	int local_type;
	int rc;
	
	rc = ft_identifier_translate(ID_TYPE_UUID, uu, sizeof(uuid_t), ID_TYPE_UID_OR_GID, (void **) &result, &local_type);
	if (rc == 0) {
		switch (local_type) {
			case MBR_REC_TYPE_GROUP:
				(*id_type) = ID_TYPE_GID;
				break;
				
			case MBR_REC_TYPE_USER:
				(*id_type) = ID_TYPE_UID;
				break;
				
			default:
				(*id_type) = -1;
				break;
		}
		
		(*id) = (*result);
		free(result);
	}
	
	return rc;
}
