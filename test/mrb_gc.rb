assert 'MrbGC.gc' do
  assert_kind_of MrbState::MrbGC, MrbState.gc
end

assert 'MrbGC.live' do
  assert_true 0 < MrbState.gc.live
end

assert 'MrbGC.live_after_mark' do
  assert_true 0 < MrbState.gc.live_after_mark
end

assert 'MrbGC.threshold' do
  assert_true 0 < MrbState.gc.threshold
end

assert 'MrbGC.interval_ratio' do
  assert_true 0 < MrbState.gc.interval_ratio
end

assert 'MrbGC.step_ratio' do
  assert_true 0 < MrbState.gc.step_ratio
end

assert 'MrbGC.majorgc_old_threshold' do
  assert_true 0 <= MrbState.gc.majorgc_old_threshold
end
