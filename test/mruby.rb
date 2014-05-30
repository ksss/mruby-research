assert 'Mruby::MRB_GC_ARENA_SIZE' do
  assert_true 0 < Mruby::MRB_GC_ARENA_SIZE
end

assert 'Mruby.nan_boxing?' do
  assert_include [true,false], Mruby.nan_boxing?
end

assert 'Mruby.live' do
  assert_true 0 < Mruby.live
end

assert 'Mruby.gc_interval_ratio' do
  assert_true 0 < Mruby.gc_interval_ratio
end

assert 'Mruby.gc_step_ratio' do
  assert_true 0 < Mruby.gc_step_ratio
end
