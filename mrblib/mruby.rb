class Object
  def to_RBasic
    Mrb::RBasic.new(self)
  end

  def to_RClass
    Mrb::RClass.new(self)
  end

  def to_RString
    Mrb::RString.new(self)
  end
end
