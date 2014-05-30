assert 'MrbState::RString.new' do
  r = MrbState::RString.new("")
  assert_equal MrbState::RString, r.class
  assert_equal MrbState::RBasic, r.class.superclass
  assert_equal "MRB_TT_STRING", r.tt
end

assert 'Object#to_RString' do
  r = "foo".to_RString
  assert_equal MrbState::RString, r.class
  assert_equal MrbState::RBasic, r.class.superclass
  assert_raise(ArgumentError){ [].to_RString }
end

assert 'MrbState::RString::RSTRING_EMBED_LEN_MAX' do
  assert_true 0 < MrbState::RString::RSTRING_EMBED_LEN_MAX
end

assert 'MrbState::RString#shared?' do
  assert_false "foo".to_RString.shared?
  assert_true "fooooooooooooooooooooooooooooooooooooooooooo".dup.to_RString.shared?
end

assert 'MrbState::RString#nofree?' do
  assert_false "foo".to_RString.nofree?
  assert_true :sym.to_s.to_RString.nofree?
end

assert 'MrbState::RString#embed?' do
  assert_true "foo".to_RString.embed?
  assert_false :sym.to_s.to_RString.embed?
end

assert 'MrbState::RString#capa' do
  assert_equal "foo".to_RString.capa, MrbState::RString::RSTRING_EMBED_LEN_MAX
end

