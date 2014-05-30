assert 'Mrb::RString.new' do
  r = Mrb::RString.new("")
  assert_equal Mrb::RString, r.class
  assert_equal Mrb::RBasic, r.class.superclass
  assert_equal "MRB_TT_STRING", r.tt
end

assert 'Object#to_RString' do
  r = "foo".to_RString
  assert_equal Mrb::RString, r.class
  assert_equal Mrb::RBasic, r.class.superclass
  assert_raise(ArgumentError){ [].to_RString }
end

assert 'Mrb::RString::RSTRING_EMBED_LEN_MAX' do
  assert_true 0 < Mrb::RString::RSTRING_EMBED_LEN_MAX
end

assert 'Mrb::RString#shared?' do
  assert_false "foo".to_RString.shared?
  assert_true "fooooooooooooooooooooooooooooooooooooooooooo".dup.to_RString.shared?
end

assert 'Mrb::RString#nofree?' do
  assert_false "foo".to_RString.nofree?
  assert_true :sym.to_s.to_RString.nofree?
end

assert 'Mrb::RString#embed?' do
  assert_true "foo".to_RString.embed?
  assert_false :sym.to_s.to_RString.embed?
end

assert 'Mrb::RString#capa' do
  assert_equal "foo".to_RString.capa, Mrb::RString::RSTRING_EMBED_LEN_MAX
end

