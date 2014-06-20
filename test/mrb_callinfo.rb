assert 'MrbState::MrbContext::MrbCallinfo#mid' do
  assert_kind_of Symbol, MrbState.c.ci.mid
end

assert 'MrbState::MrbContext::MrbCallinfo#proc' do
  assert_kind_of Proc, MrbState.c.ci.proc
end

assert 'MrbState::MrbContext::MrbCallinfo#stackent' do
  assert_equal self, MrbState.c.ci.stackent
end

assert 'MrbState::MrbContext::MrbCallinfo#nregs' do
  assert_kind_of Fixnum, MrbState.c.ci.nregs
end

assert 'MrbState::MrbContext::MrbCallinfo#ridx' do
  assert_true 0 < MrbState.c.ci.ridx
end

assert 'MrbState::MrbContext::MrbCallinfo#eidx' do
  assert_true 0 < MrbState.c.ci.eidx
end
