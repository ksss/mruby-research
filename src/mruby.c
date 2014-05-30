/**
 * mruby-mruby
 */

#include <mruby.h>
#include <mruby/value.h>
#include <mruby/hash.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/variable.h>
#include <mruby/class.h>
#include <mruby/khash.h>

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
rclass_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;

  mrb_get_args(mrb, "o", &obj);
  switch (mrb_type(obj)) {
    case MRB_TT_CLASS:
    case MRB_TT_MODULE:
      break;
    default:
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "MrbRClass can not set %S", obj);
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
rstring_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;

  mrb_get_args(mrb, "o", &obj);
  if (mrb_type(obj) != MRB_TT_STRING)
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "MrbRString can not set %S", obj);
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

void
mrb_mruby_mruby_gem_init(mrb_state* mrb) {
  struct RClass *rbasic = mrb_define_class(mrb, "MrbRBasic", mrb->object_class);
  struct RClass *rclass = mrb_define_class(mrb, "MrbRClass", rbasic);
  struct RClass *rstring = mrb_define_class(mrb, "MrbRString", rbasic);

  mrb_define_method(mrb, rbasic, "initialize", rbasic_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rbasic, "tt", rbasic_tt, MRB_ARGS_NONE());
  mrb_define_method(mrb, rbasic, "color", rbasic_color, MRB_ARGS_NONE());
  mrb_define_method(mrb, rbasic, "flags", rbasic_flags, MRB_ARGS_NONE());

  mrb_define_method(mrb, rclass, "initialize", rclass_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "super", rclass_super, MRB_ARGS_NONE());

  mrb_define_const(mrb, rstring, "RSTRING_EMBED_LEN_MAX", mrb_fixnum_value(RSTRING_EMBED_LEN_MAX));
  mrb_define_method(mrb, rstring, "initialize", rstring_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rstring, "shared?", rstring_shared_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "nofree?", rstring_nofree_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "embed?", rstring_embed_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "capa", rstring_capa, MRB_ARGS_NONE());
}

void
mrb_mruby_mruby_gem_final(mrb_state* mrb) {
}
