#include "http.h" /* the HTTP facil.io extension */
#include "test.h"

// We'll use this callback in `http_listen`, to handles HTTP requests
void on_request(http_s *request);

// These will contain pre-allocated values that we will use often
FIOBJ HTTP_HEADER_X_DATA;
char *init_str    = "init";
char *decrypt_str = "decrypt";
char *encrypt_str = "encrypt";
char *reset_str   = "reset";

// Listen to HTTP requests and start facil.io
int main(void) {
  // allocating values we use often
  HTTP_HEADER_X_DATA = fiobj_str_new("X-Data", 6);
  // listen on port 3000 and any available network binding (NULL == 0.0.0.0)
  http_listen("3000", NULL, .on_request = on_request, .log = 1);
  // start the server
  fio_start(.threads = 1);
  // deallocating the common values
  fiobj_free(HTTP_HEADER_X_DATA);
}

// provide APIs to be called by the Service layer
// the test.c file give detail explains
void on_request(http_s *request) {
  // puts(path);
  char *path = fiobj_obj2cstr(request->path).data;

  // http://localhost:3000/reset{level}
  if(strstr(path,reset_str)){
    puts("reset!");
    if(strstr(path,"0")){
      puts("reset 0!");
      reset(0);
    }
    if(strstr(path,"1")){
      puts("reset 1!");
      reset(1);
    }
    if(strstr(path,"2")){
      puts("reset 2!");
      reset(2);
    }
    if(strstr(path,"3")){
      puts("reset 3!");
      reset(3);
    }
    
    generatePKmod();

    http_send_body(request, "0K", 2);
  }

  // http://localhost:3000/init
  if(strstr(path,init_str)){
    puts("init!");
    initial();
    http_send_body(request, "0K", 2);
  }

  // http://localhost:3000/decrypt
  if(strstr(path,decrypt_str)){
    puts("decrypt!");
    char result = decrypt();
    if(result == '0'){
      http_send_body(request, "0", 1);
    }
    if(result == '1'){
       http_send_body(request, "1", 1);
    }
  }

  // http://localhost:3000/encrypt{0,1}
  if(strstr(path,encrypt_str)){
    if(strstr(path,"0")){
      puts("encrypt 0!");
      encrypt_zero();
      http_send_body(request, "0K", 2);
    }
    if(strstr(path,"1")){
      puts("encrypt 1!");
      encrypt_one();
      http_send_body(request, "0K", 2);
    }
  }

}

