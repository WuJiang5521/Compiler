//
// Created by WuJiang on 2018/5/30.
//

#include "tree.h"
#include <fstream>

Base::Base(int type) {
    this->node_type = type;
}

Stm::Stm(int type) : Base(type) {}

Exp::Exp(int type) : Base(type) {}

Program::Program(const std::string &name): Base(N_PROGRAM) {
    this->name = name;
}

void Program::addDefine(Define *define) {
    if(this->define == nullptr) this->define = define;
}

Define::Define(): Base(N_DEFINE) {
    label_def.clear();
    const_def.clear();
    type_def.clear();
    var_def.clear();
    function_def.clear();
}

void Define::addLabel(LabelDef *def) {
    label_def.push_back(def);
}

void Define::addConst(ConstDef *def) {
    const_def.push_back(def);
}

void Define::addType(TypeDef *def) {
    type_def.push_back(def);
}

void Define::addVar(VarDef *def) {
    var_def.push_back(def);
}

void Define::addFunction(FunctionDef *def) {
    function_def.push_back(def);
}

Body::Body(): Base(N_BODY) {
    stms.clear();
}

void Body::addStm(Stm *stm) {
    stms.push_back(stm);
}

Situation::Situation(): Base(N_SITUATION) {
    match_list.clear();
}

void Situation::addMatch(Exp *exp) {
    match_list.push_back(exp);
}

LabelDef::LabelDef(int index): Base(N_LABEL_DEF) {
    label_index = index;
}

ConstDef::ConstDef(const std::string &name, Exp *val): Base(N_CONST_DEF) {
    this->name = name;
    this->value = val;
}

TypeDef::TypeDef(const std::string &name, Type *type): Base(N_TYPE_DEF) {
    this->name = name;
    this->type = type;
}

VarDef::VarDef(const std::string &name, Type *type): Base(N_VAR_DEF) {
    this->name = name;
    this->type = type;
    this->initializing_value = nullptr;
}

VarDef::VarDef(const std::string &name, Type *type, Value *initialize_value): Base(N_VAR_DEF) {
    this->name = name;
    this->type = type;
    this->initializing_value = initialize_value;
}

FunctionDef::FunctionDef(const std::string &name): Base(N_FUNCTION_DEF) {
    this->name = name;
    args_type.clear();
    args_name.clear();
}

void FunctionDef::addArgs(const std::string &arg_name, Type *arg_type) {
    args_name.push_back(arg_name);
    args_type.push_back(arg_type);
}

void FunctionDef::setReturnType(Type *rtn_type) {
    if(this->rtn_type == nullptr) this->rtn_type = rtn_type;
}

void FunctionDef::addDefine(Define *def) {
    if(define == nullptr) define = def;
}

AssignStm::AssignStm(const std::string &left, Exp *right): Stm(N_ASSIGN_STM) {
    this->left_value = left;
    this->right_value = right;
}

WithStm::WithStm(const std::string &name): Stm(N_WITH_STM) {
    this->name = name;
}

CallStm::CallStm(const std::string &name): Stm(N_CALL_STM) {
    this->name = name;
    args.clear();
}

void CallStm::addArgs(Exp *exp) {
    this->args.push_back(exp);
}

LabelStm::LabelStm(const int &label): Stm(N_LABEL_STM) {
    this->label = label;
}

IfStm::IfStm(): Stm(N_IF_STM) {}

void IfStm::setCondition(Exp *cond) {
    condition = cond;
}

void IfStm::addFalse() {
    this->false_do = new Body();
}

CaseStm::CaseStm(Exp *obj): Stm(N_CASE_STM) {
    object = obj;
    situations.clear();
}

void CaseStm::addSituation(Situation *situation) {
    situations.push_back(situation);
}

ForStm::ForStm(const std::string &iter, Exp* start, Exp* end, int step): Stm(N_FOR_STM) {
	this->iter = iter;
    this->start = start;
    this->end = end;
    this->step = step;
}

WhileStm::WhileStm(Exp *cond): Stm(N_WHILE_STM) {
    condition = cond;
}

RepeatStm::RepeatStm(): Stm(N_REPEAT_STM) {}

void RepeatStm::setCondition(Exp *cond) {
    if (condition == nullptr) condition = cond;
}

GotoStm::GotoStm(int label) : Stm(label) {
    this->label = label;
}

MonocularExp::MonocularExp(int op_code, Exp *oprand): Exp(N_MONOCULAR_EXP) {
    this->op_code = op_code;
    this->operand = oprand;
}

BinaryExp::BinaryExp(int op_code, Exp *operand1, Exp *operand2): Exp(N_BINARY_EXP) {
    this->op_code = op_code;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

CallExp::CallExp(const std::string &name): Exp(N_CALL_STM) {
    this->name = name;
    args.clear();
}

void CallExp::addArgs(Exp *exp) {
    args.push_back(exp);
}

ConstantExp::ConstantExp(Value *val): Exp(N_CONSTANT_EXP) {
    value = val;
}

VariableExp::VariableExp(const std::string &name): Exp(N_VARIABLE_EXP) {
    this->name = name;
}

MemoryExp::MemoryExp(ADDRESS addr): Exp(N_MEMORY_EXP) {
    address = addr;
}

Type::Type(): Base(N_TYPE) {
    address = addr;
}

std::string getString(Value *value) {
	std::string str;
	if (value == nullptr) str = "NULL";
	else
		switch (value->base_type) {
			case T_INTEGER: {
				char val[10];
				sprintf(val, "%d", value->integer_value);
				str.append(val);
			}
				break;
			case T_REAL: {
				char val[10];
				sprintf(val, "%.2f", value->real_value);
				str.append(val);
			}
				break;
			case T_CHAR: {
				str.append("\'");
				str.append(value->char_value);
				str.append("\'");
			}
				break;
			case T_BOOLEAN: {
				if(value->boolean_value) str.append("true");
				else str.append("false");
			}
				break;
			case T_SET: case T_ARRAY: case T_RECORD: {
				str.append("[");
				for (auto child: value->children_value) {
					str.append(getString(child));
					str.append(",");
				}
				str.append("]");
			}
			default: {
                str.append("\"There is something wrong. The type is unrecognised.\"");
            }
		}
	return str;
}

std::string getString(Base *ori_node) {
    std::string str;
    if (ori_node == nullptr) str = "NULL";
    else
        switch (ori_node->node_type) {
            case N_PROGRAM: {
                auto *node = (Program*)ori_node;
                str.append("{");
                str.append("name:\"");
                str.append(node->name);
                str.append("\",");
                str.append("define:");
                str.append(getString(node->define));
                str.append(",");
                str.append("body:");
                str.append(getString(node->body));
                str.append(",}");
            }
                break;
            case N_DEFINE: {
                auto *node = (Define*)ori_node;
                str.append("{");
                str.append("label: [");
                for (auto stm: node->label_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("const: [");
                for (auto stm: node->const_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("type: [");
                for (auto stm: node->type_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("var: [");
                for (auto stm: node->var_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("function: [");
                for (auto stm: node->function_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("}");
            }
                break;
            case N_BODY: {
                auto *node = (Body*)ori_node;
                str.append("[");
                for (auto stm: node->stms) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("]");
            }
                break;
            case N_SITUATION: {
				auto *node = (Situation*)ori_node;
                str.append("{match_list:[");
                for (auto match_item: node->match_list) {
                    str.append(getString(match_item));
                    str.append(",");
                }
                str.append("], to_do:");
                str.append(getString(node->solution));
                str.append("}");
            }
                break;
            case N_LABEL_DEF: {
				auto *node = (LabelDef*)ori_node;
                str.append("{label_def: ");
                char id[100];
                sprintf(id, "%d", node->label_index);
                str.append(id);
                str.append("}");
            }
                break;
            case N_CONST_DEF: {
            	auto *node = (ConstDef*)ori_node;
                str.append("{const_name: \"");
                str.append(node->name);
                str.append("\", const_value: ");
                str.append(getString(node->value));
                str.append("}");
            }
                break;
            case N_TYPE_DEF: {
				auto *node = (TypeDef*)ori_node;
                str.append("{type_name: \"");
                str.append(node->name);
                str.append("\", structure: ");
                str.append(getString(node->type));
                str.append("}");
            }
                break;
            case N_VAR_DEF: {
            	auto *node = (VarDef*)ori_node;
                str.append("{var_name: \"");
                str.append(node->name);
                str.append("\", structure: ");
                str.append(getString(node->type));
                if (node->initialize_value != nullptr) {
                	str.append(", init_value: ");
                	str.append(getString(node->initialize_value));
                }
                str.append("}");
            }
                break;
            case N_FUNCTION_DEF: {
            	auto *node = (FunctionDef*)ori_node;
                str.append("{func_name: \"");
                str.append(node->name);
                str.append("\", args: [");
                for (int i = 0; i < node->args_name.size(); i++) {
                	str.append("{arg_name:\"");
                	str.append(node->args_name[i]);
                	str.append("\", arg_type:");
                	str.append(getString(node->args_type[i]));
                	str.append("},")
                }
                str.append("]");
                if (node->rtn_type != nullptr) {
	                str.append(", return_type: ");
	                str.append(getString(node->rtn_type));
	            }
                if (node->define != nullptr) {
	                str.append(", defines: ");                
	                str.append(getString(node->define));
	            }
                str.append(", body: ");
                str.append(getString(node->body));
                str.append("}");
            }
                break;
            case N_ASSIGN_STM: {
				auto *node = (AssignStm*)ori_node;
                str.append("{left:\"");
                str.append(node->left_value);
                str.append("\",right:");
                str.append(getString(node->right_value));
                str.append("}");
            }
                break;
            case N_CALL_STM: {
				auto *node = (CallStm*)ori_node;
                str.append("{func:\"");
                str.append(node->name);
                str.append("\",args:[");
                for (auto arg: node->args) {
                	str.append(getString(arg));
                	str.append(",");
                }
                str.append("]}");
            }
                break;
            case N_CASE_STM: {
				auto *node = (CaseStm*)ori_node;
                str.append("{switch_item:\"");
                str.append(getString(node->object));
                str.append("\",situations:[");
                for (auto situation: node->situations) {
                    str.append(getString(situation));
                    str.append(",");
                }
                str.append("]}");
            }
                break;
            case N_FOR_STM: {
				auto *node = (ForStm*)ori_node;
                str.append("{iter:\"");
                str.append(node->iter);
                str.append("\",start:");
                str.append(getString(node->start));
                str.append(",end:");
                str.append(getString(node->end));
                str.append(",step:");
                if(step == 1) str.append("1");
                else str.append("-1");
                str.append(",body:");
                str.append(getString(node->body));
                str.append("]}");
            }
                break;
            case N_GOTO_STM: {
            	auto *node = (GotoStm*)ori_node;
                str.append("{goto:");
                char label[100];
                sprintf(label, "%d", node->label);
                str.append(label);
                str.append("}");
            }
                break;
            case N_IF_STM: {
				auto *node = (IfStm*)ori_node;
                str.append("{condition:");
                str.append(getString(node->condition));
                str.append(",true_body:");
                str.append(getString(node->true_do));
                if(node->false_do != nullptr) {
                	str.append(",false_body:");
                	str.append(getString(node->false_do));
                }
                str.append("}");
            }
                break;
            case N_LABEL_STM: {
				auto *node = (LabelStm*)ori_node;
                str.append("{label: ");
                char id[100];
                sprintf(id, "%d", node->label);
                str.append(id);
                str.append("}");
            }
                break;
            case N_REPEAT_STM: {
            	auto *node = (RepeatStm*)ori_node;
                str.append("{body:");
                str.append(getString(node->loop));
                str.append(",condition:");
                str.append(getString(node->condition));
                str.append("}");
            }
                break;
            case N_WHILE_STM: {
				auto *node = (WhileStm*)ori_node;
                str.append("{condition:");
                str.append(getString(node->condition));
                str.append(",body:");
                str.append(getString(node->loop));
                str.append("}");
            }
                break;
            case N_WITH_STM: {
            	auto *node = (WithStm*)ori_node;
                str.append("{with_var:\"");
                str.append(node->name);
                str.append("\",body:");
                str.append(getString(node->body));
                str.append("}");
            }
                break;
            case N_BINARY_EXP: {
                auto *node = (BinaryExp*)ori_node;
                str.append("{bin_op:\"");
                str.append(getOpNameByID(node->op_code));
                str.append("\",operand1:");
                str.append(getString(node->operand1));
                str.append("\",operand2:");
                str.append(getString(node->operand2));
                str.append("}");
            }
                break;
            case N_CALL_EXP: {
				auto *node = (CallExp*)ori_node;
                str.append("{func:\"");
                str.append(node->name);
                str.append("\",args:[");
                for (auto arg: node->args) {
                	str.append(getString(arg));
                	str.append(",");
                }
                str.append("]}");
            }
                break;
            case N_CONSTANT_EXP: {
                auto *node = (ConstantExp*)ori_node;
                str.append("{const_value:");
                str.append(getString(node->value));
                str.append("}");
            }
                break;
            case N_MEMORY_EXP: {
                auto *node = (MemoryExp*)ori_node;
                str.append("{mem_addr:");
                char hex_addr[100];
                sprintf(hex_addr, "%lx", node->address);
                str.append("\"}");
            }
                break;
            case N_MONOCULAR_EXP: {
                auto *node = (MonocularExp*)ori_node;
                str.append("{mon_op:\"");
                str.append(getOpNameByID(node->op_code));
                str.append("\",operand:");
                str.append(getString(node->operand));
                str.append("}");
            }
                break;
            case N_VARIABLE_EXP: {
                auto *node = (VariableExp*)ori_node;
                str.append("{var_name:\"");
                str.append(node->name);
                str.append("\"}");
            }
                break;
            case N_TYPE: {
            	auto *node = (Type*)ori_node;
            	switch (value->base_type) {
					case T_INTEGER: {
		                str.append("\"integer\"");
					}
						break;
					case T_REAL: {
						str.append("\"real\"");
					}
						break;
					case T_CHAR: {
						str.append("\"char\"");
					}
						break;
					case T_BOOLEAN: {
						str.append("\"boolean\"");
					}
						break;
					case T_SET: {
						str.append("\"set\"");
					}
						break;
					case T_ARRAY: {
						str.append("{type:\"array\",num:");
						char num[100];
						sprintf(num, "%d", node->children_num);
						str.append(num);
						str.append(",child_type:");
						str.append(getString(node->child_type[0]));
						str.append("}");
					}
						break;
					case T_RECORD: {
						str.append("{type:\"record\",child_type:[");
						for(auto child: node->child_type) {
							str.append("{name:\"");
							str.append(child->name);
							str.append("\", type:")
							str.append(getString(child));
							str.append("},");
						str.append("]}");
					}
						break;
					default: {
		                if (value->base_type < type_list.size()) str.append(type_list[value->base_type]->name);
		                else str.append("\"There is something wrong. The type cannot be recognised.\"");
		            }
				}
            }
            	break;
            default: {
                str.append("\"There is something wrong. The node is unrecognised.\"");
            }
        }
    return str;
}

void printTree(std::string filename, Base *root) {
    std::string str = getString(root);
    std::ofstream SaveFile(filename + ".json");
    SaveFile << str;
    SaveFile.close();
}
