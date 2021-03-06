# c-mpwalg
C implementation of the [Masterpassword
Algorithm](https://masterpassword.lyndir.com/). Includes thin python bindings.



## Get password from secret, site, name, type, and counter.

### C
Password is written to result_buffer. Returns -1 if somethings goes wrong.
``` c
int password(const char* secret,
             size_t secret_size,
             const char* site_name,
             size_t site_name_size,
             const char* full_name,
             size_t full_name_size,
             const char* site_result_type,
             size_t site_result_type_size,
             size_t counter,
             char* result_buffer,
             size_t result_buffer_size);
```
### Python

Same as the c api except no sizes, nor a result buffer is neeeded.

Will throw an exception if something goes wrong instead of returning -1.

``` python
def password(secret,
             site_name,
             full_name,
             site_result_type,
             counter)
```


# Algorithm documentation.

## Phase 1: Your identity

We employ the SCRYPT cryptographic function to derive a 64-byte
cryptographic key from the user’s name and master password using a fixed
set of parameters.

Your identity is defined by your key. This key unlocks all of your doors.
Your master key is the cryptographic result of two components:

1. Your <name> (identification)
2. Your <master password> (authentication)

Your master password is your personal secret and your name scopes that secret
to your identity.  Together, they create a cryptographic identifier that
is unique to your person.

```
masterKey = SCRYPT( key, seed, N, r, p, dkLen )
key = <master password>
seed = scope + LEN(<name>) + <name>
N = 32768
r = 8
p = 2
dkLen = 64

```

scope and name are coded as UTF-8. `LEN(<name>)` is represented as a 32 bit-
big-endian-, unsigned-integer.

### Corresponding C function.
``` c
int main_key(const char* secret,
             size_t secret_size,
             const char* name,
             size_t name_size,
             uint8_t* result_buffer,
             size_t result_buffer_size);
```

## Phase 2: Your site key "com.lyndir.masterpassword"

Your site key is a derivative from your master key when it is used to
unlock the door to a specific site. Your site key is the result of two
components:

1. Your <site name> (identification)
2. Your <masterkey> (authentication)
3. Your <site counter> 

Your master key ensures only your identity has access to this key and your
site name scopes the key to your site.  The site counter ensures you can
easily create new keys for the site should a key become
compromised. Together, they create a cryptographic identifier that is
unique to your account at this site.

```
siteKey = HMAC-SHA-256( key, seed )
key = <master key>
seed = scope . LEN(<site name>) . <site name> . <counter>
```


We employ the HMAC-SHA-256 cryptographic function to derive a 32-byte
cryptographic site key from the from the site name and master key scoped
to a given counter value.

### Corresponding C function.
``` c
int site_key(const char* site_name,
             size_t site_name_length,
             const uint8_t key[64],
             size_t key_size,
             uint32_t counter,
             uint8_t result_buffer[64],
             size_t result_buffer_size);
```


## Phase 3: Your site password 

Your site password is an identifier derived from your site key in
compoliance with the site’s password policy.

The purpose of this step is to render the site’s cryptographic key into a
format that the site’s password input will accept.

Master Password declares several site password formats and uses these
pre-defined password “templates” to render the site key legible.

```
template = templates[ <site key>[0] % LEN( templates ) ]

for i in 0..LEN( template ) 
  passChars = templateChars[ template[i] ]2
  passWord[i] = passChars[ <site key>[i+1] % LEN( passChars ) ] 
```

We resolve a template to use for the password from the site key’s first
byte.  As we iterate the template, we use it to translate site key bytes
into password characters.  The result is a site password in the form
defined by the site template scoped to our site key.

This password is then used to authenticate the user for his account at
this site.

### Corresponding C function.

``` c
int site_password(uint8_t site_key[32],
                  const char* result_type,
                  size_t result_type_size,
                  char* result_buffer,
                  size_t result_buffer_size);
```



## Output Templates:
In an effort to enforce increased password entropy, a common consensus has
developed among account administrators that passwords should adhere to
certain arbitrary password policies.  These policies enforce certain rules
which must be honoured for an account password to be deemed acceptable.

As a result of these enforcement practices, Master Password’s site key
output must necessarily adhere to these types of policies.  Since password
policies are governed by site administrators and not standardized, Master
Password defines several password templates to make a best-effort attempt at
generating site passwords that conform to these policies while also keeping
its output entropy as high as possible under the constraints.
