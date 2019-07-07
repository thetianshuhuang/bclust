/**
 * Bayesian Clustering Python C API Core Module
 */

#include <Python.h>

/**
 * Core Numpy Import
 */
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL BAYESIAN_CLUSTERING_C_ARRAY_API
#include <numpy/arrayobject.h>

#include <gibbs.h>
#include <dpm.h>
#include <mfm.h>
#include <normal_wishart.h>
#include <mixture.h>
#include <select.h>


/**
 * Module Methods
 */
static PyMethodDef ModuleMethods[] = {
    {
        "gibbs_iter",
        (PyCFunction) gibbs_iter_py,
        METH_VARARGS,
        DOCSTRING_GIBBS_ITER
    },
    {
        "init_model",
        (PyCFunction) init_model_capsules_py,
        METH_VARARGS,
        DOCSTRING_INIT_MODEL_CAPSULES
    },
    {
        "update_hyperparameters",
        (PyCFunction) update_params_py,
        METH_VARARGS,
        DOCSTRING_UPDATE_PARAMS
    },
    {
        "pairwise_probability",
        (PyCFunction) pairwise_probability_py,
        METH_VARARGS,
        DOCSTRING_PAIRWISE_PROBABILITY
    },
    {NULL, NULL, 0, NULL}
};


/**
 * Module Definitions
 */
static struct PyModuleDef ModuleDef = {
    PyModuleDef_HEAD_INIT,
    "core",
    "C accelerator functions for bayesian clustering algorithms",
    -1,
    ModuleMethods
};


/**
 * Module Initialization
 * Capsules are loaded separately from function definitions
 */
PyMODINIT_FUNC PyInit_core()
{
    import_array();

    PyObject *mod = PyModule_Create(&ModuleDef);
    if(mod == NULL) { return NULL; }

    // -- Capsules - Models ---------------------------------------------------
    PyModule_AddObject(
        mod, "MODEL_DPM", PyCapsule_New(
            &DPM_METHODS, MODEL_METHODS_API, NULL));
    PyModule_AddObject(
        mod, "MODEL_MFM", PyCapsule_New(
            &MFM_METHODS, MODEL_METHODS_API, NULL));

    // -- Capsules - Components -----------------------------------------------    
    PyModule_AddObject(
        mod, "COMPONENT_NORMAL_WISHART", PyCapsule_New(
            &NORMAL_WISHART, COMPONENT_METHODS_API, NULL));

    return mod;
}

