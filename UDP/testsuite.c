#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "udp.h"
#include "erreur.h"
#include "nombre.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int est_ip_valide(const char *ip);
int est_port_valide(int port);

/** Montage de la fixation - appelé avant chaque cas de test. **/
int init_suite(void) { return 0; }

int clean_suite(void) { return 0; }

/****** Cas de test - validation de l'adresse IP *****/
void test_validation_ip(void) {
    CU_ASSERT(est_ip_valide("192.168.1.1"));
    CU_ASSERT(!est_ip_valide("999.999.999.999"));
    CU_ASSERT(!est_ip_valide("256.256.256.256"));
    CU_ASSERT(!est_ip_valide("abc.def.ghi.jkl"));
}

/**** Cas de test - validation du port *****/ 
void test_validation_port(void) {
    CU_ASSERT(est_port_valide(8080));
    CU_ASSERT(!est_port_valide(10));
    CU_ASSERT(!est_port_valide(70000));
}

/******************* Lancement des tests ***********************/
int main(void) {
    CU_pSuite pSuite = NULL;
    unsigned int status = 0;
    
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
        
    pSuite = CU_add_suite("Test module serveur", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if ((NULL == CU_add_test(pSuite, "Cas de test - validation de l'adresse IP", test_validation_ip)) ||
        (NULL == CU_add_test(pSuite, "Cas de test - validation du port", test_validation_port))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_NORMAL);
    if (CUE_SUCCESS != CU_basic_run_tests())
        return CU_get_error();
    
    status = CU_get_number_of_tests_failed();
    CU_basic_show_failures(CU_get_failure_list());
    
    CU_cleanup_registry();
    return status;
}
