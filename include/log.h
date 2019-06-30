#ifndef LOG_H
#define LOG_H

#define log_f1(x, a) log_die(x, "fatal", 1, a)
#define log_f2(x, a,b) log_die(x, "fatal", 2, a,b)
#define log_f3(x, a,b,c) log_die(x, "fatal", 3, a,b,c)
#define log_f4(x, a,b,c,d) log_die(x, "fatal", 4, a,b,c,d)
#define log_f5(x, a,b,c,d,e) log_die(x, "fatal", 5, a,b,c,d,e)
#define log_f6(x, a,b,c,d,e,f) log_die(x, "fatal", 6, a,b,c,d,e,f)
#define log_f7(x, a,b,c,d,e,f,g) log_die(x, "fatal", 7, a,b,c,d,e,f,g)
#define log_f8(x, a,b,c,d,e,f,g,h) log_die(x, "fatal", 8, a,b,c,d,e,f,g,h)
#define log_f9(x, a,b,c,d,e,f,g,h,i) log_die(x, "fatal", 9, a,b,c,d,e,f,g,h,i)
#define log_fs1(x, a) log_die_sys(x, "fatal", 1, a)
#define log_fs2(x, a,b) log_die_sys(x, "fatal", 2, a,b)
#define log_fs3(x, a,b,c) log_die_sys(x, "fatal", 3, a,b,c)
#define log_fs4(x, a,b,c,d) log_die_sys(x, "fatal", 4, a,b,c,d)
#define log_fs5(x, a,b,c,d,e) log_die_sys(x, "fatal", 5, a,b,c,d,e)
#define log_fs6(x, a,b,c,d,e,f) log_die_sys(x, "fatal", 6, a,b,c,d,e,f)
#define log_fs7(x, a,b,c,d,e,f,g) log_die_sys(x, "fatal", 7, a,b,c,d,e,f,g)
#define log_fs8(x, a,b,c,d,e,f,g,h) log_die_sys(x, "fatal", 8, a,b,c,d,e,f,g,h)
#define log_fs9(x, a,b,c,d,e,f,g,h,i) log_die_sys(x, "fatal", 9, a,b,c,d,e,f,g,h,i)

#define log_e1(a) log_put(2, "error", 1, a)
#define log_e2(a,b) log_put(2, "error", 2, a,b)
#define log_e3(a,b,c) log_put(2, "error", 3, a,b,c)
#define log_e4(a,b,c,d) log_put(2, "error", 4, a,b,c,d)
#define log_e5(a,b,c,d,e) log_put(2, "error", 5, a,b,c,d,e)
#define log_e6(a,b,c,d,e,f) log_put(2, "error", 6, a,b,c,d,e,f)
#define log_e7(a,b,c,d,e,f,g) log_put(2, "error", 7, a,b,c,d,e,f,g)
#define log_e8(a,b,c,d,e,f,g,h) log_put(2, "error", 8, a,b,c,d,e,f,g,h)
#define log_e9(a,b,c,d,e,f,g,h,i) log_put(2, "error", 9, a,b,c,d,e,f,g,h,i)
#define log_es1(a) log_put_sys(2, "error", 1, a)
#define log_es2(a,b) log_put_sys(2, "error", 2, a,b)
#define log_es3(a,b,c) log_put_sys(2, "error", 3, a,b,c)
#define log_es4(a,b,c,d) log_put_sys(2, "error", 4, a,b,c,d)
#define log_es5(a,b,c,d,e) log_put_sys(2, "error", 5, a,b,c,d,e)
#define log_es6(a,b,c,d,e,f) log_put_sys(2, "error", 6, a,b,c,d,e,f)
#define log_es7(a,b,c,d,e,f,g) log_put_sys(2, "error", 7, a,b,c,d,e,f,g)
#define log_es8(a,b,c,d,e,f,g,h) log_put_sys(2, "error", 8, a,b,c,d,e,f,g,h)
#define log_es9(a,b,c,d,e,f,g,h,i) log_put_sys(2, "error", 9, a,b,c,d,e,f,g,h,i)

#define log_w1(a) log_put(3, "warning", 1, a)
#define log_w2(a,b) log_put(3, "warning", 2, a,b)
#define log_w3(a,b,c) log_put(3, "warning", 3, a,b,c)
#define log_w4(a,b,c,d) log_put(3, "warning", 4, a,b,c,d)
#define log_w5(a,b,c,d,e) log_put(3, "warning", 5, a,b,c,d,e)
#define log_w6(a,b,c,d,e,f) log_put(3, "warning", 6, a,b,c,d,e,f)
#define log_w7(a,b,c,d,e,f,g) log_put(3, "warning", 7, a,b,c,d,e,f,g)
#define log_w8(a,b,c,d,e,f,g,h) log_put(3, "warning", 8, a,b,c,d,e,f,g,h)
#define log_w9(a,b,c,d,e,f,g,h,i) log_put(3, "warning", 9, a,b,c,d,e,f,g,h,i)
#define log_ws1(a) log_put_sys(3, "warning", 1, a)
#define log_ws2(a,b) log_put_sys(3, "warning", 2, a,b)
#define log_ws3(a,b,c) log_put_sys(3, "warning", 3, a,b,c)
#define log_ws4(a,b,c,d) log_put_sys(3, "warning", 4, a,b,c,d)
#define log_ws5(a,b,c,d,e) log_put_sys(3, "warning", 5, a,b,c,d,e)
#define log_ws6(a,b,c,d,e,f) log_put_sys(3, "warning", 6, a,b,c,d,e,f)
#define log_ws7(a,b,c,d,e,f,g) log_put_sys(3, "warning", 7, a,b,c,d,e,f,g)
#define log_ws8(a,b,c,d,e,f,g,h) log_put_sys(3, "warning", 8, a,b,c,d,e,f,g,h)
#define log_ws9(a,b,c,d,e,f,g,h,i) log_put_sys(3, "warning", 9, a,b,c,d,e,f,g,h,i)

#define log_i1(a) log_put(4, "info", 1, a)
#define log_i2(a,b) log_put(4, "info", 2, a,b)
#define log_i3(a,b,c) log_put(4, "info", 3, a,b,c)
#define log_i4(a,b,c,d) log_put(4, "info", 4, a,b,c,d)
#define log_i5(a,b,c,d,e) log_put(4, "info", 5, a,b,c,d,e)
#define log_i6(a,b,c,d,e,f) log_put(4, "info", 6, a,b,c,d,e,f)
#define log_i7(a,b,c,d,e,f,g) log_put(4, "info", 7, a,b,c,d,e,f,g)
#define log_i8(a,b,c,d,e,f,g,h) log_put(4, "info", 8, a,b,c,d,e,f,g,h)
#define log_i9(a,b,c,d,e,f,g,h,i) log_put(4, "info", 9, a,b,c,d,e,f,g,h,i)

#define log_d1(a) log_put(5, "debug", 1, a)
#define log_d2(a,b) log_put(5, "debug", 2, a,b)
#define log_d3(a,b,c) log_put(5, "debug", 3, a,b,c)
#define log_d4(a,b,c,d) log_put(5, "debug", 4, a,b,c,d)
#define log_d5(a,b,c,d,e) log_put(5, "debug", 5, a,b,c,d,e)
#define log_d6(a,b,c,d,e,f) log_put(5, "debug", 6, a,b,c,d,e,f)
#define log_d7(a,b,c,d,e,f,g) log_put(5, "debug", 7, a,b,c,d,e,f,g)
#define log_d8(a,b,c,d,e,f,g,h) log_put(5, "debug", 8, a,b,c,d,e,f,g,h)
#define log_d9(a,b,c,d,e,f,g,h,i) log_put(5, "debug", 9, a,b,c,d,e,f,g,h,i)

extern int log_level;

// bin/make-h liblog/*.c
void    log_die(int, char const *, int, ...);
void    log_die_sys(int, char const *, int, ...);
void    log_init(void);
void    log_put(int, char const *, int, ...);
void    log_put_sys(int, char const *, int, ...);
void    log_usage(char const *, char const *);

#endif
