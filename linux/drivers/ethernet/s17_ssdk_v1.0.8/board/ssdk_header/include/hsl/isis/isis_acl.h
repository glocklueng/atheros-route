/*
 * Copyright (c) 2007-2009 Atheros Communications, Inc.
 * All rights reserved.
 *
 */
/**
 * @defgroup isis_acl ISIS_ACL
 * @{
 */
#ifndef _ISIS_ACL_H_
#define _ISIS_ACL_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "fal/fal_acl.h"

sw_error_t isis_acl_init(a_uint32_t dev_id);

sw_error_t isis_acl_reset(a_uint32_t dev_id);

#ifdef IN_ACL
#define ISIS_ACL_INIT(rv, dev_id) \
    { \
        rv = isis_acl_init(dev_id); \
        SW_RTN_ON_ERROR(rv); \
    }

#define ISIS_ACL_RESET(rv, dev_id) \
    { \
        rv = isis_acl_reset(dev_id); \
        SW_RTN_ON_ERROR(rv); \
    }
#else
#define ISIS_ACL_INIT(rv, dev_id)
#define ISIS_ACL_RESET(rv, dev_id)
#endif

#ifdef HSL_STANDALONG

HSL_LOCAL sw_error_t
isis_acl_list_creat(a_uint32_t dev_id, a_uint32_t list_id,
                    a_uint32_t list_pri);

HSL_LOCAL sw_error_t
isis_acl_list_destroy(a_uint32_t dev_id, a_uint32_t list_id);

HSL_LOCAL sw_error_t
isis_acl_rule_add(a_uint32_t dev_id, a_uint32_t list_id,
                  a_uint32_t rule_id, a_uint32_t rule_nr,
                  fal_acl_rule_t * rule);

HSL_LOCAL sw_error_t
isis_acl_rule_delete(a_uint32_t dev_id, a_uint32_t list_id,
                     a_uint32_t rule_id, a_uint32_t rule_nr);

HSL_LOCAL sw_error_t
isis_acl_rule_query(a_uint32_t dev_id, a_uint32_t list_id,
                    a_uint32_t rule_id, fal_acl_rule_t * rule);

HSL_LOCAL sw_error_t
isis_acl_list_bind(a_uint32_t dev_id, a_uint32_t list_id,
                   fal_acl_direc_t direc, fal_acl_bind_obj_t obj_t,
                   a_uint32_t obj_idx);

HSL_LOCAL sw_error_t
isis_acl_list_unbind(a_uint32_t dev_id, a_uint32_t list_id,
                     fal_acl_direc_t direc, fal_acl_bind_obj_t obj_t,
                     a_uint32_t obj_idx);

HSL_LOCAL sw_error_t
isis_acl_status_set(a_uint32_t dev_id, a_bool_t enable);

HSL_LOCAL sw_error_t
isis_acl_status_get(a_uint32_t dev_id, a_bool_t * enable);

HSL_LOCAL sw_error_t
isis_acl_list_dump(a_uint32_t dev_id);

HSL_LOCAL sw_error_t
isis_acl_rule_dump(a_uint32_t dev_id);

HSL_LOCAL sw_error_t
isis_acl_port_udf_profile_set(a_uint32_t dev_id, fal_port_t port_id,
                              fal_acl_udf_type_t udf_type,
                              a_uint32_t offset, a_uint32_t length);

HSL_LOCAL sw_error_t
isis_acl_port_udf_profile_get(a_uint32_t dev_id, fal_port_t port_id,
                              fal_acl_udf_type_t udf_type,
                              a_uint32_t * offset, a_uint32_t * length);

HSL_LOCAL sw_error_t
isis_acl_rule_active(a_uint32_t dev_id, a_uint32_t list_id,
                      a_uint32_t rule_id, a_uint32_t rule_nr);

HSL_LOCAL sw_error_t
isis_acl_rule_deactive(a_uint32_t dev_id, a_uint32_t list_id,
                      a_uint32_t rule_id, a_uint32_t rule_nr);

#endif

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _ISIS_ACL_H_ */
/**
 * @}
 */
