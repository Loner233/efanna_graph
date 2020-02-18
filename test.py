import ctypes
lib = ctypes.cdll.LoadLibrary("./cmake-build-debug/libefanna2e.so")
string1 = "./cmake-build-debug/siftsmall/siftsmall_base.fvecs"
string2 = "./saved_data"
b_string1 = string1.encode("utf-8")
b_string2 = string2.encode("utf-8")
s1 = ctypes.c_char_p(b_string1)
s2 = ctypes.c_char_p(b_string2)
lib.foo(s1,s2,10,20,30,40,50)
