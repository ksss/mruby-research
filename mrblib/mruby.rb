class Object
  def to_RBasic
    MrbRBasic.new(self)
  end

  def to_RClass
    MrbRClass.new(self)
  end

  def to_RString
    MrbRString.new(self)
  end
end
