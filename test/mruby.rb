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

assert 'MrbState.live' do
  assert_true 0 < MrbState.live
end

assert 'MrbState.gc_live_after_mark' do
  assert_true 0 < MrbState.gc_live_after_mark
end

assert 'MrbState.gc_threshold' do
  assert_true 0 < MrbState.gc_threshold
end

assert 'MrbState.gc_interval_ratio' do
  assert_true 0 < MrbState.gc_interval_ratio
end

assert 'MrbState.gc_step_ratio' do
  assert_true 0 < MrbState.gc_step_ratio
end

assert 'MrbState.majorgc_old_threshold' do
  assert_true 0 < MrbState.majorgc_old_threshold
end

assert 'MrbState.symidx' do
  assert_kind_of Fixnum, MrbState.symidx
end

assert 'MrbState.size' do
  assert_kind_of Fixnum, MrbState.size
end
