#ifndef DIE_H
#define DIE_H

#define die_absent(u,f) log_f(1, "user \"",u,"\" not in \"",f,"\"")
#define die_chdir(d)    log_fs(111, "could not chdir to \"",d,"\"");
#define die_copy()      log_fs(111, "could not copy the file")
#define die_exist(u,f)  log_f(1, "user \"",u,"\" already in \"",f,"\"")
#define die_invalid(s)  log_f(1, "invalid character(s) in the ",s)
#define die_nomem()     log_fs(111, "could not allocate memory")
#define die_open(p)     log_fs(111, "could not open \"",p,"\"")
#define die_read(f)     log_fs(111, "could not read line from \"",f,"\"")
#define die_rename(f,t) log_fs(111, "could not rename \"",f,"\" to \"",t,"\"")
#define die_write()     log_fs(111, "could not write to the temporary pass file")
#define die_exec(x)     log_fs(111, "could not execute \"",x,"\"")

#endif