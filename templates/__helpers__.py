def type_convert(type):
    if type == int:
        return "int"
    elif type == float:
        return "float"
    elif type == str:
        return "std::string";

#for conversion during the Json value grabbing
def type_convert2(type):
    if type == int:
        return "Int"
    elif type == float:
        return "Float"
    elif type == str:
        return "String";

def is_primitive(type):
    if type == int:
        return True
    elif type == float:
        return True
    elif type == str:
        return True
    return False

#JSONcpp requires double quotes
def fix_name(name):
   name2 = name[1:-1]
   return "\\\"" + name2 + "\\\""

#for accessing elements by name in JSONcpp array
def double_quotes(name):
   name2 = name[1:-1]
   return "\"" + name2 + "\""