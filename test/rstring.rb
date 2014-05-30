assert 'Mruby::RString.new' do
  r = Mruby::RString.new("")
  assert_equal Mruby::RString, r.class
  assert_equal Mruby::RBasic, r.class.superclass
  assert_equal "MRB_TT_STRING", r.tt
end

assert 'Object#to_RString' do
  r = "foo".to_RString
  assert_equal Mruby::RString, r.class
  assert_equal Mruby::RBasic, r.class.superclass
  assert_raise(ArgumentError){ [].to_RString }
end

assert 'Mruby::RString::RSTRING_EMBED_LEN_MAX' do
  assert_true 0 < Mruby::RString::RSTRING_EMBED_LEN_MAX
end

assert 'Mruby::RString#shared?' do
  assert_false "foo".to_RString.shared?
  assert_true "fooooooooooooooooooooooooooooooooooooooooooo".dup.to_RString.shared?
end

assert 'Mruby::RString#nofree?' do
  assert_false "foo".to_RString.nofree?
  assert_true :sym.to_s.to_RString.nofree?
end

assert 'Mruby::RString#embed?' do
  assert_true "foo".to_RString.embed?
  assert_false :sym.to_s.to_RString.embed?
end

assert 'Mruby::RString#capa' do
  assert_equal "foo".to_RString.capa, Mruby::RString::RSTRING_EMBED_LEN_MAX
end

