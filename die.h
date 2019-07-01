#ifndef DIE_H
#define DIE_H

#define die_open(p)     log_fs3(111, "could not open \"",p,"\"")
#define die_read(f)     log_fs3(111, "could not read line from \"",f,"\"")
#define die_nomem()     log_fs1(111, "could not allocate memory")
#define die_exist(u,f)  log_f5(1, "user \"",u,"\" already in \"",f,"\"")
#define die_absent(u,f) log_f5(1, "user \"",u,"\" not in \"",f,"\"")
#define die_write()     log_fs1(111, "could not write to the temporary pass file")
#define die_rename(f,t) log_fs5(111, "could not rename \"",f,"\" to \"",t,"\"")
#define die_invalid(s)  log_f2(1, "invalid character(s) in the ",s)
#define die_copy()      log_fs1(111, "could not copy the file")

#endif
