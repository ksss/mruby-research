assert 'MrbState::RProc::MrbIrep.new' do
  irep = MrbState::RProc::MrbIrep.new do
    "this is block"
  end
  assert_equal MrbState::RProc::MrbIrep, irep.class
  assert_equal Object, irep.class.superclass
  assert_raise(ArgumentError){ MrbState::RProc::MrbIrep.new(1) }
end

assert 'MrbState::RProc::MrbIrep#nlocals' do
  irep = MrbState::RProc::MrbIrep.new(Proc.new{})
  assert_equal 1, irep.nlocals
end

assert 'MrbState::RProc::MrbIrep#nregs' do
  irep = MrbState::RProc::MrbIrep.new(Proc.new{})
  assert_equal 2, irep.nregs
end

assert 'MrbState::RProc::MrbIrep#flags' do
  irep = MrbState::RProc::MrbIrep.new(Proc.new{})
  assert_equal 0, irep.flags
end

assert 'MrbState::RProc::MrbIrep#iseq' do
  irep = MrbState::RProc::MrbIrep.new(Proc.new{})
  assert_equal [8388613, 8388649], irep.iseq
end

assert 'MrbState::RProc::MrbIrep#pool' do
  irep = MrbState::RProc::MrbIrep.new { {pool:"string"} }
  assert_equal ["string"], irep.pool
end

assert 'MrbState::RProc::MrbIrep#syms' do
  irep = MrbState::RProc::MrbIrep.new { {pool:"string"} }
  assert_equal [:pool], irep.syms
end

assert 'MrbState::RProc::MrbIrep#reps' do
  irep = MrbState::RProc::MrbIrep.new { }
  assert_equal [], irep.reps

  irep = MrbState::RProc::MrbIrep.new { Proc.new{}; Proc.new{}; Proc.new{} }
  assert_equal 3, irep.reps.length
end

assert 'MrbState::RProc::MrbIrep#lv' do
  irep = MrbState::RProc::MrbIrep.new { }
  assert_equal [], irep.lv

  irep = MrbState::RProc::MrbIrep.new {|a,b,c| }
  assert_equal [{name: :a, r: 1}, {name: :b, r: 2}, {name: :c, r: 3}], irep.lv
end

assert 'MrbState::RProc::MrbIrep#filename' do
  irep = MrbState::RProc::MrbIrep.new { }
  assert_equal "", irep.filename
end

assert 'MrbState::RProc::MrbIrep#lines' do
  irep = MrbState::RProc::MrbIrep.new { }
  assert_equal [], irep.lines
end
