assert 'MrbState::MRB_GC_ARENA_SIZE' do
  assert_true 0 < MrbState::MRB_GC_ARENA_SIZE
end

assert 'MrbState::MRB_INT_MIN' do
  assert_true MrbState::MRB_INT_MIN < 0
end

assert 'MrbState::MRB_INT_MAX' do
  assert_true 0 < MrbState::MRB_INT_MAX
end

assert 'MrbState.nan_boxing?' do
  assert_include [true,false], MrbState.nan_boxing?
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

assert 'MrbState.symidx' do
  assert_true 0 < MrbState.majorgc_old_threshold
end

assert 'MrbState.symidx' do
  assert_kind_of Fixnum, MrbState.symidx
end
