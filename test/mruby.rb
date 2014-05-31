assert 'MrbState::MRB_GC_ARENA_SIZE' do
  assert_true 0 < MrbState::MRB_GC_ARENA_SIZE
end

assert 'MrbState::MRB_FUNCALL_ARGC_MAX' do
  assert_true 0 < MrbState::MRB_FUNCALL_ARGC_MAX
end

assert 'MrbState::MRB_HEAP_PAGE_SIZE' do
  assert_true 0 < MrbState::MRB_HEAP_PAGE_SIZE
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

assert 'MrbState::MRB_IVHASH_INIT_SIZE' do
  assert_true 0 < MrbState::MRB_IVHASH_INIT_SIZE
end

assert 'MrbState.use_float?' do
  assert_include [true,false], MrbState.use_float?
end

assert 'MrbState.nan_boxing?' do
  assert_include [true,false], MrbState.nan_boxing?
end

assert 'MrbState.word_boxing?' do
  assert_include [true,false], MrbState.word_boxing?
end

assert 'MrbState.use_iv_seglist?' do
  assert_include [true,false], MrbState.use_iv_seglist?
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
