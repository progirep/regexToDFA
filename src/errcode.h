/*
 * errcode.h: internal interface for error reporting
 *
 * Copyright (C) 2009 Red Hat Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 * Author: David Lutterkort <lutter@redhat.com>
 */

#ifndef ERRCODE_H_
#define ERRCODE_H_

#include "internal.h"
/* Include augeas.h for the error codes */
#include "augeas.h"

/*
 * Error details in a separate struct that we can pass around
 */
struct error {
    aug_errcode_t  code;
    int            minor;
    char          *details;       /* Human readable explanation */
    const char    *minor_details; /* Human readable version of MINOR */
};

void report_error(struct error *err, aug_errcode_t errcode,
                  const char *format, ...)
    ATTRIBUTE_FORMAT(printf, 3, 4);

#define ERR_BAIL(obj) if ((obj)->error->code != AUG_NOERROR) goto error;

#define ERR_NOMEM(cond, obj)                             \
    if (cond) {                                          \
        report_error((obj)->error, AUG_ENOMEM, NULL);    \
        goto error;                                      \
    }

#define ERR_REPORT(obj, code, fmt ...)          \
    report_error((obj)->error, code, ## fmt)

#define ERR_THROW(cond, obj, code, fmt ...)             \
    do {                                                \
        if (cond) {                                     \
            report_error((obj)->error, code, ## fmt);   \
            goto error;                                 \
        }                                               \
    } while(0)

#endif


/*
 * Local variables:
 *  indent-tabs-mode: nil
 *  c-indent-level: 4
 *  c-basic-offset: 4
 *  tab-width: 4
 * End:
 */