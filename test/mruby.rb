assert 'MrbState.mrbconf' do
  assert_true MrbState.mrbconf.has_key?("MRB_NAN_BOXING")
end

assert 'MrbState::MRB_INT_BIT' do
  assert_include [16,32,64], MrbState::MRB_INT_BIT
end

assert 'MrbState::MRB_INT_MIN' do
  assert_true MrbState::MRB_INT_MIN < 0
end

assert 'MrbState::MRB_INT_MAX' do
  assert_true 0 < MrbState::MRB_INT_MAX
end

assert 'MrbState.symidx' do
  assert_kind_of Fixnum, MrbState.symidx
end

assert 'MrbState.size' do
  assert_kind_of Fixnum, MrbState.size
end
