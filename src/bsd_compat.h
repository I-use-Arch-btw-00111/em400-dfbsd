#ifndef BSD_COMPAT_H
#define BSD_COMPAT_H

#if defined(__FreeBSD__) || defined(__DragonFly__)

#include <pthread.h>
#include <pthread_np.h>

/* Map Linux pthread_setname_np (int return) to BSD void function */
#ifndef pthread_setname_np
#define pthread_setname_np(th, name) (pthread_set_name_np((th), (name)), 0)
#endif

/* Map Linux pthread_getname_np to BSD function */
#ifndef pthread_getname_np
#define pthread_getname_np(th, name, len) (pthread_get_name_np((th), (name), (len)), 0)
#endif

#endif /* __FreeBSD__ || __DragonFly__ */

#endif /* BSD_COMPAT_H */
