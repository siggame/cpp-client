def type_convert(type):
    if type == int:
        return "int"
    elif type == float:
        return "float"
    elif type == str:
        return "std::string";

def is_primitive(type):
    if type == int:
        return True
    elif type == float:
        return True
    elif type == str:
        return True
    return False
