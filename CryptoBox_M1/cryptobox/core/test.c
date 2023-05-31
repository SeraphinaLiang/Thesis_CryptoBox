#include "test.h"
#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include "dghv.h"

typedef __prikey* privatekey;
typedef __pubkey_set* publickey;
typedef __cit*    ciphertext;
typedef __sec_setting* sec_setting;

sec_setting para;   // the security parameter choice
privatekey prikey;  // private key
publickey  pubkey;  // public key
randstate rs;       // random state

// restore parameter & public/private key from saved file
int initial(){
    // read seed
    unsigned long seed = get_seed();
   
    
    set_randstate(rs, seed);
    // read parameter
    init_sec_para(&para);
    printf("read_parameters\n");
    read_sec_para(para, "/Users/liangyinqi/Desktop/xcode/second_try/cryptobox/key_setting/parameters");
    // read key
    init_sk(&prikey, para);
    init_pkset(&pubkey, para);

    printf("read_pubkey\n");
    read_pubkey(pubkey, "/Users/liangyinqi/Desktop/xcode/second_try/cryptobox/key_setting/public_key.key");
    printf("read_prikey\n");
    read_prikey(prikey, "/Users/liangyinqi/Desktop/xcode/second_try/cryptobox/key_setting/private_key.key");

    return 0;
}

// reset parameter according to security level , generate & save new public/private key pair
int reset(int level){
    // generate parameter
    unsigned long seed = get_seed();
    // save seed
    FILE *f = fopen("/Users/liangyinqi/Desktop/xcode/second_try/cryptobox/key_setting/seed", "w");
    fprintf(f, " %lu", seed);
    fclose(f);
    
    
    init_sec_para(&para);
    set_default_para(para, level);       //set_default_para(para, TOY); 
    mpf_set_default_prec(2 * para->eta + para->gam);
    set_randstate(rs, seed);
    printf("save_parameters\n");
    save_sec_para(para, "/Users/liangyinqi/Desktop/xcode/second_try/cryptobox/key_setting/parameters");
    // generate key
    init_sk(&prikey, para);
    init_pkset(&pubkey, para);
    gen_prikey(prikey, rs);
    gen_pubkey(pubkey, prikey, para, rs, 1);
    expand_p2y(pubkey, prikey, para->prec, rs);
    // save key
    printf("save_pubkey\n");
    save_pubkey(pubkey, "/Users/liangyinqi/Desktop/xcode/second_try/cryptobox//key_setting/public_key.key");
    printf("save_prikey\n");
    save_prikey(prikey, "/Users/liangyinqi/Desktop/xcode/second_try/cryptobox//key_setting/private_key.key");

    return 0;
}

// encrypt a '1' value , save generated ciphertext to 'ctext/one.txt'
int encrypt_one(){
    ciphertext c1;
    init_cit(&c1, para->Theta);
    unsigned long m = 1;
   // printf("m1= %lu\n", m1);
    DGHV_encrypt(c1, m, pubkey, para, rs);
   // expend_cit(c, pubkey);
//    gmp_printf("c1= %Zd\n", c1->c);
   // res = DGHV_decrypt(c, prikey);
   // printf("m1 decrypt res= %lu\n", res);
 
    FILE *f = fopen("/Users/liangyinqi/Desktop/xcode/second_try/cryptobox/ctext/one.txt", "w");
    gmp_fprintf(f, "%Zd\n",c1->c);
    fclose(f);
    clear_cit(c1);

    return 0;
}

// encrypt a '0' value , save generated ciphertext to 'ctext/zero.txt'
int encrypt_zero(){
    ciphertext c1;
    init_cit(&c1, para->Theta);
    unsigned long m = 0;
    DGHV_encrypt(c1, m, pubkey, para, rs);
   // gmp_printf("c1= %Zd\n", c1->c);

    FILE *f = fopen("/Users/liangyinqi/Desktop/xcode/second_try/cryptobox/ctext/zero.txt", "w");
    gmp_fprintf(f, "%Zd\n",c1->c);
    fclose(f);
    clear_cit(c1);

    return 0;
}

// decrypt one bit value, which ciphertext in 'decrypt_text/cin.txt', return a '1' or '0'
char decrypt(){
    unsigned long result;
    unsigned long one = 1;
    unsigned long zero = 0;
    char val;

    mpz_t cin;
    mpz_init(cin);

    FILE *f = fopen("/Users/liangyinqi/Desktop/xcode/second_try/cryptobox/decrypt_text/cin.txt","r");
    gmp_fscanf(f,"%Zd",&cin);
   // gmp_printf("%Zd\n",cin);

    result = DGHV_decrypt_2(cin, prikey);
    printf("decrypt result= %lu\n", result);

    mpz_clear(cin);
    fclose(f);
    
    if(result==one) val = '1';
    if(result==zero) val = '0';

    return val;
}

// save the pk0 to 'key_setting/pk0.txt'
int generatePKmod(){

   // gmp_printf("pk0= %Zd\n", pubkey->pks[0]);

    FILE *out = fopen("/Users/liangyinqi/Desktop/xcode/second_try/cryptobox/key_setting/pk0.txt", "wt");
    gmp_fprintf(out, "%Zd\n",pubkey->pks[0]);
    fclose(out);

    return 0;
}

// a simplify version of decrypt function
unsigned long DGHV_decrypt_2(mpz_t ciphertext, __prikey* prikey){
 	mpz_t plaintext;
 	mpz_init(plaintext);
 	mpz_mod(plaintext,ciphertext,prikey->sk);
 	mpz_mod_ui(plaintext,plaintext,2);
    unsigned long pl = mpz_get_ui(plaintext);
    mpz_clear(plaintext);
 	return pl;
}


/*
int test(){

    ciphertext c1, c2, c3;
    init_cit(&c1, para->Theta);
    init_cit(&c2, para->Theta);
    init_cit(&c3, para->Theta);

    unsigned long m1 = 0, m2 = 1, res;
    printf("m1= %lu\n", m1);
    DGHV_encrypt(c1, m1, pubkey, para, rs);
    expend_cit(c1, pubkey);
    //gmp_printf("c1= %Zd\n", c1->c);

    res = DGHV_decrypt(c1, prikey);
    printf("m1 decrypt res= %lu\n", res);

    printf("m2= %lu\n", m2);
    DGHV_encrypt(c2, m2, pubkey, para, rs);
    expend_cit(c2, pubkey);
    //gmp_printf("c2= %Zd\n", c2->c);
    res = DGHV_decrypt(c2, prikey1);
    printf("m2 decrypt res= %lu\n", res);

    ciphertext cadd, cmul;
    init_cit(&cadd, para->Theta);
    init_cit(&cmul, para->Theta);
    // text add & mul
    mpz_t pk0 = pubkey1->pks[0];
    evaluate_add(cadd,c1,c2,pubkey->pks[0]);
    evaluate_mul(cmul,c1,c2, pubkey->pks[0]);

    res = DGHV_decrypt(cadd,prikey1);
    printf("add res= %lu\n", res);
    res = DGHV_decrypt(cmul,prikey1);
    printf("mul res= %lu\n", res);
//-----------------------------------------------------

    char** copy_bufmap;
    char** bufmap = (char**)malloc(2*sizeof(char*));
    printf("save_str\n");
    bufmap[0] = format_ciphertext_str(c1);
    printf("save_str\n");
    bufmap[1] = format_ciphertext_str(c2);

    printf("save_str\n");

    save_str(bufmap, 2, "CCC");
    printf("save_str\n");
    copy_bufmap = read_str("CCC");
    printf("save_str\n");

    ciphertext c4, c5;
    init_cit(&c4, para->Theta);
    init_cit(&c5, para->Theta);

    format_str_ciphertext(copy_bufmap[1],  c4);
    format_str_ciphertext(copy_bufmap[2],  c5);

    if(mpz_cmp(c1->c, c4->c)==0) printf("OK\n");
    if(mpz_cmp(c2->c, c5->c)==0) printf("OK\n");

//---------------------------------------------
    free(para);
    clear_sk(prikey);
    clear_pkset(pubkey);

    free(para);
    clear_sk(prikey);
    clear_pkset(pubkey);
    clear_cit(c1);
    clear_cit(c2);
    clear_cit(c3);
   
    return 0;

}
 */
