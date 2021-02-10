#define EX_INTERRUPT_HANDLER(a)	extern void a(void)

#define ik_ivg14		14
#define ik_timer		6
#define	EX_INT_ENABLE	1

extern void app_init(void);
extern void register_handler_ex(int inum,void (*func)(void),int mode);
