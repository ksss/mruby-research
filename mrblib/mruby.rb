class Object
  def to_mrb_value
    MrbState::MrbValue.new(self)
  end

  def to_RBasic
    MrbState::RBasic.new(self)
  end
end

class Class
  def to_RClass
    MrbState::RClass.new(self)
  end
end

class String
  def to_RString
    MrbState::RString.new(self)
  end
end

class Proc
  def to_RProc
    MrbState::RProc.new(self)
  end
end
