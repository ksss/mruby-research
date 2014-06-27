assert 'MrbState.root_c' do
  assert_kind_of MrbState::MrbContext, MrbState.root_c
end

assert 'MrbState.c' do
  assert_kind_of MrbState::MrbContext, MrbState.c
end

assert 'MrbState::MrbContext.size' do
  assert_true 0 < MrbState::MrbContext.size
end

assert 'MrbState::MrbContext#prev' do
  assert_kind_of MrbState::MrbContext, MrbState.c.prev
end

assert 'MrbState::MrbContext#stack_at' do
  root_c = MrbState.root_c
  assert_equal root_c, root_c.stack_at(0)
end

assert 'MrbState::MrbContext#stack_index' do
  assert_true 0 < MrbState.c.stack_index
end

assert 'MrbState::MrbContext#stbase' do
  assert_equal self, MrbState.root_c.stbase
end

assert 'MrbState::MrbContext#stend' do
  assert_nil MrbState.root_c.stend
end

assert 'MrbState::MrbContext#ci' do
  assert_kind_of MrbState::MrbContext::MrbCallinfo, MrbState.root_c.ci
end

assert 'MrbState::MrbContext#cibase' do
  assert_kind_of MrbState::MrbContext::MrbCallinfo, MrbState.root_c.cibase
end

assert 'MrbState::MrbContext#ciend' do
  assert_kind_of MrbState::MrbContext::MrbCallinfo, MrbState.root_c.ciend
end

assert 'MrbState::MrbContext#rescue' do
  assert_kind_of Array, MrbState.root_c.rescue
end

assert 'MrbState::MrbContext#rsize' do
  assert_kind_of Fixnum, MrbState.root_c.rsize
end

assert 'MrbState::MrbContext#ensure' do
  assert_kind_of Array, MrbState.root_c.ensure
end

assert 'MrbState::MrbContext#esize' do
  assert_kind_of Fixnum, MrbState.root_c.esize
end

assert 'MrbState::MrbContext#status' do
  assert_equal "MRB_FIBER_RUNNING", MrbState.root_c.status
end

assert 'MrbState::MrbContext#fib' do
  assert_kind_of Fiber, MrbState.root_c.fib
end

assert 'MrbState::MrbContext#ci_length' do
  assert_true 0 < MrbState.root_c.ci_length
end

assert 'MrbState::MrbContext#stack_length' do
  assert_true 0 < MrbState.root_c.stack_length
  assert_true MrbState.root_c.stack_index <= MrbState.root_c.stack_length
end
