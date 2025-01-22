#include "m_pd.h"

#include <math.h>
#include <stdbool.h>

typedef struct _clipper {
    t_object obj;

    float cutoff;
    bool cutoff_specified;

    float fsig;
} t_clipper;

void clipper_tilde_setup(void);
void* clipper_new(t_floatarg f);
void clipper_dsp(t_clipper* x, t_signal** sp);
t_int* clipper_perform(t_int* w);

float fsign(float x);

static t_class* clipper_class;

void clipper_tilde_setup(void) {
    clipper_class = class_new(
        gensym("clipper~"),         // Name
        (t_newmethod) clipper_new,  // Constructor
        NULL,                       // Destructor (unused)
        sizeof(t_clipper),          // Size
        CLASS_DEFAULT,              // Graphical representation
        A_DEFFLOAT,                 // Data input format
        0                           
    );

    CLASS_MAINSIGNALIN(clipper_class, t_clipper, fsig);
    class_addmethod(clipper_class, (t_method) clipper_dsp, gensym("dsp"), A_CANT, 0);	
}

void* clipper_new(t_floatarg f) {
    t_clipper* x = (t_clipper*) pd_new(clipper_class);
    
    inlet_new(&x->obj, &x->obj.ob_pd, gensym("signal"), gensym("signal")); // Right inlet controls the clipping cutoff
    outlet_new(&x->obj, gensym("signal"));

    if (f) {
        x->cutoff_specified = true;
        x->cutoff = f;
    }

    return x;
}

void clipper_dsp(t_clipper* x, t_signal** sp) {
    if (sp[0]->s_sr > 0)
        dsp_add(clipper_perform, 5, x, sp[0]->s_vec /* Left inlet */, sp[1]->s_vec /* Right inlet */, sp[2]->s_vec /* Outlet */, sp[2]->s_n /* Outlet size */);
}

t_int* clipper_perform(t_int* w) {
    t_clipper* x = (t_clipper*) w[1];
    float* in = (float*) w[2];

    float* cutoff_in = (float*) w[3];

    float* out = (float*) w[4];
    int out_size = w[5];

    while (out_size--) {
        if (!x->cutoff_specified) {
            *out = (fabs(*in) > *cutoff_in ? fsign(*in) * *cutoff_in : *in);
            cutoff_in++;
        }
        else
            *out = (fabs(*in) > x->cutoff ? fsign(*in) * x->cutoff : *in);

        out++; in++;
    }

    return w + 6;
}

// Returns the sign of a float value.
float fsign(float x) {
    return (x > 0) - (x < 0);
}