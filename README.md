PassLock
========
`git://git.josuah.net/passlock` - [0.1](/tool/passlock/passlock-0.1.tgz)

PassLock is a backend for [checkpassword][1], a generic and simple password
checking interface.

It provides a set of commands to create password entries and check them.

It stores usernames, password and a path with one file per user, with a path
pattern of your choice, hashed with [argon2id][2] from [libsodium][3].

[1]: https://cr.yp.to/checkpwd.html
[2]: https://www.argon2.com/
[3]: https://download.libsodium.org/doc/

How to use it?
--------------
First create an user:

	$ passlock-set -p /etc/paslock/%u ace-ventura
	enter passphrase: sekrit

Then test that the password is recognised:

	$ printf '%s\0' "ace-ventura" "sekrit" "0" |
	  passlock-check \
	    -p /etc/paslock/%u \
	    -h /var/mail/%u/Maildir \
	  echo welcome aboard

Then use it with a checkpassword-enabled daemon:

	$ preauth-daemon passlock-check \
	    -p /etc/paslock/%u \
	    -h /var/mail/%u/Maildir \
	  authenticated-daemon

How to get it?
--------------
It requires a C compiler and the libsodium library.

	$ git clone git://code.z0.is/passlock
	$ cd passlock
	$ make install PREFIX="$PREFIX" LIBSODIUM="$libsodium"

How does it work?
-----------------
The main daemon read the password from the user logging in, execute
passlock-check and write the password to a pipe (file descriptor 3).

If the password is accurate, passlock-check then execute into its
specified program.  Otherwise, it exits with an error and nothing
more happen.

Processes running during authentication:

	preauth-daemon passlock-check -p... authenticated-daemon
	└─ passlock-check authenticated-daemon

Processes running after failure:

	preauth-daemon passlock-check -p... authenticated-daemon

Processes running after success:

	preauth-daemon passlock-check -p... authenticated-daemon
	└─ authenticated-daemon

How to configure Dovecot?
-------------------------
[Dovecot](https://dovecot.org/) can use a [checkpassword backend][d1], and
passlock works well with it. If your password file is `/var/mail/$user/pass`
owned by `mail` and your user mailbox is at `/var/mail/$user/Maildir`:

[d1]: https://doc.dovecot.org/configuration_manual/authentication/checkpassword

```
mail_location = maildir:~/Maildir

service auth {
        user = mail
}

userdb {
        driver = static
        args = uid=mail gid=mail home=/var/mail/%L{username}
}

passdb {
        driver = checkpassword
        args = /usr/bin/env passlock-check -s 10 -h /var/mail/%%u -p /var/mail/%%u/pass
}
```

I want to split local@domain into domain/local
----------------------------------------------
You can use `%d` for domain and `%l` for local part. Let me know if you have a
different way of splitting your user names into directories, maybe
non-email-style usernames.
