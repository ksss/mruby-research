/**
 * mruby-research
 */

#include <stdio.h>
#include <mruby.h>
#include <mruby/value.h>
#include <mruby/hash.h>
#include <mruby/proc.h>
#include <mruby/irep.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/variable.h>
#include <mruby/class.h>
#include <mruby/khash.h>
#include "defmrbconf.h"

static mrb_value
mrb_class_s_mrbconf(mrb_state *mrb, mrb_value mod)
{
  mrb_value h = mrb_hash_new(mrb);
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_USE_FLOAT"), mrb_bool_value(DEF_MRB_USE_FLOAT));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_INT16"), mrb_bool_value(DEF_MRB_INT16));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_INT64"), mrb_bool_value(DEF_MRB_INT64));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_NAN_BOXING"), mrb_bool_value(DEF_MRB_NAN_BOXING));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_ENDIAN_BIG"), mrb_bool_value(DEF_MRB_ENDIAN_BIG));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_WORD_BOXING"), mrb_bool_value(DEF_MRB_WORD_BOXING));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_FUNCALL_ARGC_MAX"), mrb_fixnum_value(MRB_FUNCALL_ARGC_MAX));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_HEAP_PAGE_SIZE"), mrb_fixnum_value(MRB_HEAP_PAGE_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_USE_IV_SEGLIST"), mrb_bool_value(DEF_MRB_USE_IV_SEGLIST));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_IVHASH_INIT_SIZE"), mrb_fixnum_value(MRB_IVHASH_INIT_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_GC_TURN_OFF_GENERATIONAL"), mrb_bool_value(DEF_MRB_GC_TURN_OFF_GENERATIONAL));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "KHASH_DEFAULT_SIZE"), mrb_fixnum_value(KHASH_DEFAULT_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "POOL_ALIGNMENT"), mrb_fixnum_value(POOL_ALIGNMENT));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "POOL_PAGE_SIZE"), mrb_fixnum_value(POOL_PAGE_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_STR_BUF_MIN_SIZE"), mrb_fixnum_value(MRB_STR_BUF_MIN_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_GC_ARENA_SIZE"), mrb_fixnum_value(MRB_GC_ARENA_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_GC_FIXED_ARENA"), mrb_bool_value(DEF_MRB_GC_FIXED_ARENA));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "ENABLE_STDIO"), mrb_bool_value(DEF_ENABLE_STDIO));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "DISABLE_STDIO"), mrb_bool_value(DEF_DISABLE_STDIO));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "ENABLE_DEBUG"), mrb_bool_value(DEF_ENABLE_DEBUG));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "DISABLE_DEBUG"), mrb_bool_value(DEF_DISABLE_DEBUG));
  return h;
}

static mrb_value
mrb_class_s_live(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(mrb->live);
}

static mrb_value
mrb_class_s_gc_live_after_mark(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(mrb->gc_live_after_mark);
}

static mrb_value
mrb_class_s_gc_threshold(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(mrb->gc_threshold);
}

static mrb_value
mrb_class_s_gc_interval_ratio(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(mrb->gc_interval_ratio);
}

static mrb_value
mrb_class_s_gc_step_ratio(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(mrb->gc_step_ratio);
}

static mrb_value
mrb_class_s_majorgc_old_threshold(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(mrb->majorgc_old_threshold);
}

static mrb_value
mrb_class_s_symidx(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(mrb->symidx);
}

static mrb_value
mrb_class_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(sizeof(mrb_state));
}

static mrb_value
mrb_value_class_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(sizeof(mrb_value));
}

static mrb_value
mrb_value_class_i(mrb_state *mrb, mrb_value mod)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  return mrb_fixnum_value(mrb_fixnum(obj));
}

static mrb_value
mrb_value_class_f(mrb_state *mrb, mrb_value mod)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  return mrb_float_value(mrb, mrb_float(obj));
}

static mrb_value
mrb_class_s_stack_length(mrb_state *mrb, mrb_value mod)
{
  struct mrb_context *c = mrb->c;

  return mrb_fixnum_value(c->stend - c->stbase);
}

static mrb_value
mrb_class_s_ci_length(mrb_state *mrb, mrb_value mod)
{
  struct mrb_context *c = mrb->c;

  return mrb_fixnum_value(c->ciend - c->cibase);
}

struct vtypes {
  enum mrb_vtype tt;
  const char *name;
} vtypelist [] = {
  {MRB_TT_FALSE,     "MRB_TT_FALSE"},
  {MRB_TT_FREE,      "MRB_TT_FREE"},
  {MRB_TT_TRUE,      "MRB_TT_TRUE"},
  {MRB_TT_FIXNUM,    "MRB_TT_FIXNUM"},
  {MRB_TT_SYMBOL,    "MRB_TT_SYMBOL"},
  {MRB_TT_UNDEF,     "MRB_TT_UNDEF"},
  {MRB_TT_FLOAT,     "MRB_TT_FLOAT"},
  {MRB_TT_CPTR,      "MRB_TT_CPTR"},
  {MRB_TT_OBJECT,    "MRB_TT_OBJECT"},
  {MRB_TT_CLASS,     "MRB_TT_CLASS"},
  {MRB_TT_MODULE,    "MRB_TT_MODULE"},
  {MRB_TT_ICLASS,    "MRB_TT_ICLASS"},
  {MRB_TT_SCLASS,    "MRB_TT_SCLASS"},
  {MRB_TT_PROC,      "MRB_TT_PROC"},
  {MRB_TT_ARRAY,     "MRB_TT_ARRAY"},
  {MRB_TT_HASH,      "MRB_TT_HASH"},
  {MRB_TT_STRING,    "MRB_TT_STRING"},
  {MRB_TT_RANGE,     "MRB_TT_RANGE"},
  {MRB_TT_EXCEPTION, "MRB_TT_EXCEPTION"},
  {MRB_TT_FILE,      "MRB_TT_FILE"},
  {MRB_TT_ENV,       "MRB_TT_ENV"},
  {MRB_TT_DATA,      "MRB_TT_DATA"},
  {MRB_TT_FIBER,     "MRB_TT_FIBER"},
  {MRB_TT_MAXDEFINE, NULL},
};

struct colors {
  uint32_t color:3;
  const char *name;
} colorlist [] = {
  {0, "MRB_GC_GRAY"},
  {1, "MRB_GC_WHITE_A"},
  {2, "MRB_GC_WHITE_B"},
  {3, "MRB_GC_WHITES"},
  {4, "MRB_GC_BLACK"},
  {5, NULL},
};

static const char*
tt2str(enum mrb_vtype tt)
{
  struct vtypes *vs;

  for (vs = vtypelist; vs->name; vs++) {
    if (vs->tt == tt)
      return vs->name;
  }
  return NULL;
}

static const char*
color2str(uint32_t color)
{
  struct colors *cs;

  for (cs = colorlist; cs->name; cs++) {
    if (cs->color == color)
      return cs->name;
  }
  return NULL;
}

static mrb_value
rbasic_s_ttlist(mrb_state *mrb, mrb_value klass)
{
  mrb_value h = mrb_hash_new(mrb);
  struct vtypes *vs;

  for (vs = vtypelist; vs->name; vs++) {
    mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, vs->name), mrb_fixnum_value(vs->tt));
  }
  return h;
}

static mrb_value
rbasic_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(sizeof(struct RBasic));
}

static mrb_value
rbasic_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;

  mrb_get_args(mrb, "o", &obj);
  mrb_vm_iv_set(mrb, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

static mrb_value
rbasic_tt(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  enum mrb_vtype tt = mrb_type(obj);

  return mrb_str_new_cstr(mrb, tt2str(tt));
}

static mrb_value
rbasic_color(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  uint32_t color = mrb_obj_ptr(obj)->color;

  return mrb_str_new_cstr(mrb, color2str(color));
}

static mrb_value
rbasic_flags(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_fixnum_value(mrb_obj_ptr(obj)->flags);
}

static mrb_value
rclass_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(sizeof(struct RClass));
}

static mrb_value
rclass_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;

  mrb_get_args(mrb, "o", &obj);
  switch (mrb_type(obj)) {
    case MRB_TT_CLASS:
    case MRB_TT_MODULE:
      break;
    default:
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "RClass can not set %S", obj);
  }
  mrb_vm_iv_set(mrb, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

static mrb_value
rclass_super(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_obj_value(mrb_class_ptr(obj)->super);
}

static mrb_value
rstring_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(sizeof(struct RString));
}

static mrb_value
rstring_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;

  mrb_get_args(mrb, "o", &obj);
  if (mrb_type(obj) != MRB_TT_STRING)
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "RString can not set %S", obj);
  mrb_vm_iv_set(mrb, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

static mrb_value
rstring_embed_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_bool_value(RSTRING(obj)->flags & MRB_STR_EMBED);
}

static mrb_value
rstring_nofree_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_bool_value(RSTRING(obj)->flags & MRB_STR_NOFREE);
}

static mrb_value
rstring_shared_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_bool_value(RSTRING(obj)->flags & MRB_STR_SHARED);
}

static mrb_value
rstring_capa(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_fixnum_value(RSTRING_CAPA(obj));
}

static mrb_value
rproc_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value(sizeof(struct RProc));
}

static mrb_value
rproc_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj, block;
  mrb_int argc;

  argc = mrb_get_args(mrb, "|o&", &obj, &block);
  if (argc == 2) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "RProc can set only one object");
  }
  if (!mrb_nil_p(block)) {
    obj = block;
  }
  if (mrb_type(obj) != MRB_TT_PROC)
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "RProc can not set %S", obj);
  mrb_vm_iv_set(mrb, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

static mrb_value
rproc_cfunc_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_bool_value(MRB_PROC_CFUNC_P(mrb_proc_ptr(obj)));
}

static mrb_value
rproc_strict_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_bool_value(MRB_PROC_STRICT_P(mrb_proc_ptr(obj)));
}

static mrb_value
rproc_target_class(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_obj_value(mrb_proc_ptr(obj)->target_class);
}

static mrb_value
rproc_irep(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  struct RClass *irep_class = mrb_class_get_under(mrb, mrb_obj_class(mrb, self), "MrbIrep");

  return mrb_funcall(mrb, mrb_obj_value(irep_class), "new", 1, obj);
}

static mrb_value
mrb_irep_class_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj, block;
  mrb_int argc;

  argc = mrb_get_args(mrb, "|o&", &obj, &block);
  if (argc == 2) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "MrbIrep can set only one object");
  }
  if (!mrb_nil_p(block)) {
    obj = block;
  }
  if (mrb_type(obj) != MRB_TT_PROC)
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "MrbIrep can not set %S", obj);
  mrb_vm_iv_set(mrb, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

static mrb_value
mrb_irep_class_nlocals(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_fixnum_value(mrb_proc_ptr(obj)->body.irep->nlocals);
}

static mrb_value
mrb_irep_class_nregs(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_fixnum_value(mrb_proc_ptr(obj)->body.irep->nregs);
}

static mrb_value
mrb_irep_class_flags(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));

  return mrb_fixnum_value(mrb_proc_ptr(obj)->body.irep->flags);
}

static mrb_value
mrb_irep_class_iseq(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;
  mrb_value a = mrb_ary_new_capa(mrb, irep->ilen);
  mrb_int i;

  for (i = 0; i < irep->ilen; i++) {
    mrb_ary_set(mrb, a, i, mrb_fixnum_value(irep->iseq[i]));
  }
  return a;
}

static mrb_value
mrb_irep_class_pool(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_ary_new_from_values(mrb, irep->plen, irep->pool);
}

static mrb_value
mrb_irep_class_syms(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;
  mrb_value a = mrb_ary_new_capa(mrb, irep->slen);
  mrb_int i;

  for (i = 0; i < irep->slen; i++) {
    mrb_ary_set(mrb, a, i, mrb_symbol_value(irep->syms[i]));
  }
  return a;
}

static mrb_value
mrb_irep_class_reps(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;
  mrb_value a = mrb_ary_new_capa(mrb, irep->slen);
  struct RClass *irep_class = mrb_obj_class(mrb, self);
  mrb_int i;

  for (i = 0; i < irep->rlen; i++) {
    struct RProc *proc = mrb_proc_new(mrb, irep->reps[i]);
    mrb_value new_irep = mrb_funcall(mrb, mrb_obj_value(irep_class), "new", 1, mrb_obj_value(proc));
    mrb_ary_set(mrb, a, i, new_irep);
  }
  return a;
}

static mrb_value
mrb_irep_class_lv(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;
  mrb_value a = mrb_ary_new_capa(mrb, irep->nlocals - 1);
  mrb_int i;

  if (!irep->lv)
    return mrb_ary_new(mrb);

  for (i = 0; i < irep->nlocals - 1; ++i) {
    if (irep->lv[i].name) {
      mrb_value h = mrb_hash_new(mrb);
      mrb_hash_set(mrb, h, mrb_check_intern_cstr(mrb, "name"), mrb_symbol_value(irep->lv[i].name));
      mrb_hash_set(mrb, h, mrb_check_intern_cstr(mrb, "r"), mrb_fixnum_value(irep->lv[i].r));
      mrb_ary_set(mrb, a, i, h);
    }
  }
  return a;
}

static mrb_value
mrb_irep_class_filename(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_str_new_cstr(mrb, irep->filename);
}

static mrb_value
mrb_irep_class_lines(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;
  mrb_int iseq_no;
  mrb_value a = mrb_ary_new_capa(mrb, irep->ilen);

  if (!irep->lines)
    return a;
  for (iseq_no = 0; iseq_no < irep->ilen; iseq_no++) {
    mrb_ary_set(mrb, a, iseq_no, mrb_fixnum_value(irep->lines[iseq_no]));
  }
  return a;
}

static mrb_value
mrb_irep_class_ilen(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_fixnum_value(irep->ilen);
}

static mrb_value
mrb_irep_class_plen(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_fixnum_value(irep->plen);
}

static mrb_value
mrb_irep_class_slen(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_fixnum_value(irep->slen);
}

static mrb_value
mrb_irep_class_rlen(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_fixnum_value(irep->rlen);
}

static mrb_value
mrb_irep_class_refcnt(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_vm_iv_get(mrb, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_fixnum_value(irep->refcnt);
}

void
mrb_mruby_research_gem_init(mrb_state* mrb)
{
  struct RClass *mrb_class = mrb_define_module(mrb, "MrbState");
  struct RClass *mrb_value_class = mrb_define_class_under(mrb, mrb_class, "MrbValue", mrb->object_class);
  struct RClass *mrb_context_class = mrb_define_class_under(mrb, mrb_class, "MrbContext", mrb->object_class);
  struct RClass *rbasic = mrb_define_class_under(mrb, mrb_class, "RBasic", mrb->object_class);
  struct RClass *rclass = mrb_define_class_under(mrb, mrb_class, "RClass", rbasic);
  struct RClass *rstring = mrb_define_class_under(mrb, mrb_class, "RString", rbasic);
  struct RClass *rproc = mrb_define_class_under(mrb, mrb_class, "RProc", rbasic);
  struct RClass *mrb_irep_class = mrb_define_class_under(mrb, rproc, "MrbIrep", mrb->object_class);

  mrb_define_const(mrb, mrb_class, "MRB_INT_BIT", mrb_fixnum_value(MRB_INT_BIT));
  mrb_define_const(mrb, mrb_class, "MRB_INT_MIN", mrb_fixnum_value(MRB_INT_MIN));
  mrb_define_const(mrb, mrb_class, "MRB_INT_MAX", mrb_fixnum_value(MRB_INT_MAX));
  mrb_define_class_method(mrb, mrb_class, "mrbconf", mrb_class_s_mrbconf, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "live", mrb_class_s_live, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "gc_live_after_mark", mrb_class_s_gc_live_after_mark, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "gc_threshold", mrb_class_s_gc_threshold, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "gc_interval_ratio", mrb_class_s_gc_interval_ratio, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "gc_step_ratio", mrb_class_s_gc_step_ratio, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "majorgc_old_threshold", mrb_class_s_majorgc_old_threshold, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "symidx", mrb_class_s_symidx, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "size", mrb_class_s_size, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, mrb_value_class, "size", mrb_value_class_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_value_class, "initialize", rbasic_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_value_class, "i", mrb_value_class_i, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_value_class, "f", mrb_value_class_f, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, mrb_context_class, "stack_length", mrb_class_s_stack_length, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_context_class, "ci_length", mrb_class_s_ci_length, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, rbasic, "ttlist", rbasic_s_ttlist, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, rbasic, "size", rbasic_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, rbasic, "initialize", rbasic_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rbasic, "tt", rbasic_tt, MRB_ARGS_NONE());
  mrb_define_method(mrb, rbasic, "color", rbasic_color, MRB_ARGS_NONE());
  mrb_define_method(mrb, rbasic, "flags", rbasic_flags, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, rclass, "size", rclass_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "initialize", rclass_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "super", rclass_super, MRB_ARGS_NONE());

  mrb_define_const(mrb, rstring, "RSTRING_EMBED_LEN_MAX", mrb_fixnum_value(RSTRING_EMBED_LEN_MAX));
  mrb_define_class_method(mrb, rstring, "size", rstring_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "initialize", rstring_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rstring, "shared?", rstring_shared_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "nofree?", rstring_nofree_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "embed?", rstring_embed_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "capa", rstring_capa, MRB_ARGS_NONE());

  mrb_define_const(mrb, rproc, "MRB_PROC_CFUNC", mrb_fixnum_value(MRB_PROC_CFUNC));
  mrb_define_const(mrb, rproc, "MRB_PROC_STRICT", mrb_fixnum_value(MRB_PROC_STRICT));
  mrb_define_class_method(mrb, rproc, "size", rproc_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, rproc, "initialize", rproc_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, rproc, "cfunc?", rproc_cfunc_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rproc, "strict?", rproc_strict_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rproc, "target_class", rproc_target_class, MRB_ARGS_NONE());
  mrb_define_method(mrb, rproc, "irep", rproc_irep, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_irep_class, "initialize", mrb_irep_class_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_irep_class, "nlocals", mrb_irep_class_nlocals, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "nregs", mrb_irep_class_nregs, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "flags", mrb_irep_class_flags, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "iseq", mrb_irep_class_iseq, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "pool", mrb_irep_class_pool, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "syms", mrb_irep_class_syms, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "reps", mrb_irep_class_reps, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "lv", mrb_irep_class_lv, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "filename", mrb_irep_class_filename, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "lines", mrb_irep_class_lines, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "ilen", mrb_irep_class_ilen, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "plen", mrb_irep_class_plen, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "slen", mrb_irep_class_slen, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "rlen", mrb_irep_class_rlen, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "refcnt", mrb_irep_class_refcnt, MRB_ARGS_NONE());
}

void
mrb_mruby_research_gem_final(mrb_state* mrb) {
}
