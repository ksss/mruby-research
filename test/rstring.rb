assert 'MrbRString.new' do
  r = MrbRString.new("")
  assert_equal MrbRString, r.class
  assert_equal MrbRBasic, r.class.superclass
  assert_equal "MRB_TT_STRING", r.tt
end

assert 'Object#to_RString' do
  r = "foo".to_RString
  assert_equal MrbRString, r.class
  assert_equal MrbRBasic, r.class.superclass
  assert_raise(ArgumentError){ [].to_RString }
end

assert 'MrbRString::RSTRING_EMBED_LEN_MAX' do
  assert_true 0 < MrbRString::RSTRING_EMBED_LEN_MAX
end

assert 'MrbRString#shared?' do
  assert_false "foo".to_RString.shared?
  assert_true "fooooooooooooooooooooooooooooooooooooooooooo".dup.to_RString.shared?
end

assert 'MrbRString#nofree?' do
  assert_false "foo".to_RString.nofree?
  assert_true :sym.to_s.to_RString.nofree?
end

assert 'MrbRString#embed?' do
  assert_true "foo".to_RString.embed?
  assert_false :sym.to_s.to_RString.embed?
end

assert 'MrbRString#capa' do
  assert_equal "foo".to_RString.capa, MrbRString::RSTRING_EMBED_LEN_MAX
end

