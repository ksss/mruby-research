class Object
  def to_mrb_value
    MrbState::MrbValue.new(self)
  end

  def to_RBasic
    MrbState::RBasic.new(self)
  end

  def to_RClass
    MrbState::RClass.new(self)
  end

  def to_RString
    MrbState::RString.new(self)
  end
end
