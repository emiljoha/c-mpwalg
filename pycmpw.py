import ctypes

cmpw = ctypes.CDLL('./mpw.so')
MAX_SIZE_PASSWORD = 21
password_buffer = b'\0' * MAX_SIZE_PASSWORD
cmpw.password('password',
              len('password') + 1,
              'example.org',
              len('example.org') + 1,
              'name',
              len('name') + 1,
              'Long',
              len('Long') + 1,
              1,
              password_buffer,
              21)
print(password_buffer)
