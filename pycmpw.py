import ctypes

_cmpw = ctypes.CDLL('./mpw.so')
_MAX_SIZE_PASSWORD = 21


def password(secret,
             site_name,
             full_name,
             site_result_type,
             counter):
    c_secret = ctypes.c_char_p(secret.encode('utf-8'))
    secret_size = len(secret.encode('utf-8')) + 1
    c_site_name = ctypes.c_char_p(site_name.encode('utf-8'))
    site_name_size = len(site_name.encode('utf-8')) + 1
    c_name = ctypes.c_char_p(full_name.encode('utf-8'))
    name_size = len(full_name.encode('utf-8')) + 1
    c_result_type = ctypes.c_char_p(site_result_type.encode('utf-8'))
    result_type_size = len(site_result_type.encode('utf-8')) + 1
    password_buffer = ctypes.create_string_buffer(_MAX_SIZE_PASSWORD)
    _cmpw.password(c_secret,
                   secret_size,
                   c_site_name,
                   site_name_size,
                   c_name,
                   name_size,
                   c_result_type,
                   result_type_size,
                   counter,
                   password_buffer,
                   21)
    return password_buffer.value.decode('utf-8')


if __name__ == '__main__':
    print(password("password", "example.org", "name", "Long", 1))
