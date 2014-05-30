assert 'MrbState::MRB_GC_ARENA_SIZE' do
  assert_true 0 < MrbState::MRB_GC_ARENA_SIZE
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
