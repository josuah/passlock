PassLock
========
PassLock is a simple password checking program using the [checkpassword][1]
interface.

It provides a set of commands to create password entries and check them.

It stores usernames, password and a path in a simple passwd-style file (default
to /etc/passlock/default).

The password is hashed using [argon2id][2] from [libsodium][3].

[1]: https://cr.yp.to/checkpwd.html
[2]: https://www.argon2.com/
[3]: https://download.libsodium.org/doc/

Building
--------
The only dependencies is a few of the standard libc and
the libsodium library.

The traditionnal make install uses the default, otherwise:
	make install PREFIX="$PREFIX" LIBSODIUM="$libsodium"

How it works
------------
The main daemon read the password from the user logging in, execute
passlock-check and write the password to a pipe (file descriptor 3).

If the password is accurate, passlock-check then execute into its
specified program.  Otherwise, it exits with an error and nothing
more happen.

Processes running during authentication:
	preauth-daemon passlock-check authenticated-daemon
	└─ passlock-check authenticated-daemon

Processes running after failure:
	preauth-daemon passlock-check authenticated-daemon

Processes running after success:
	preauth-daemon passlock-check authenticated-daemon
	└─ authenticated-daemon
