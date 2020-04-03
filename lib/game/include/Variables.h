#pragma once

#include <vector>
#include <string>
#include <Player.h>
#include <iostream>
#include <unordered_map>
#include <memory>



namespace game {
    
    //using inheritance to support dynamic typing of variables
    //visitor pattern for extensible variable behaviours
    class Variable {
        virtual ~Variable() = default;
        virtual void accept(VariableVisitor& visitor) = 0;
    };

//-------------------------------------variable types-------------------------------
    class IntVariable : public Variable{
        public:
            IntVariable(int val) : value{val} {}
            void accept (VariableVisitor& visitor) override {return visitor.visit(*this);}
            int value = 0;
    }

    class BoolVariable : public Variable{
        public:
            IntVariable(bool val) : value{val} {}
            void accept (VariableVisitor& visitor) override {return visitor.visit(*this);}
            bool value = true;
    }

    class StringVariable : public Variable{
        public:
            StringVariable(const std::string& val) : value{val} {}
            void accept (VariableVisitor& visitor) override {return visitor.visit(*this);}
            std::string value;
    }

    class VectorVariable : public Variable {
        public:
            void accept (VariableVisitor& visitor) override {return visitor.visit(*this);}
            std::vector<Variable> value;
    }

    class MapVariable : public Variable {
        public:
            void accept (VariableVisitor& visitor) override {return visitor.visit(*this);}
            std::unordered_map<std::string, Variable> value;
    }

//-----------------------------------------------------------------------

    class VariableVisitor {
        virtual ~VariableVisitor() = default;
        virtual void visit(IntVariable& variable) = 0;
        virtual void visit(BoolVariable& variable) = 0;
        virtual void visit(StringVariable& variable) = 0;
        virtual void visit(VectorVariable& variable) = 0;
        virtual void visit(MapVariable& variable) = 0;
    }

    class Variables {
        public:
            //return variable held and allows modification directly
            Variable getVariable(const std::string& variableName) const;
            
            //take variable by value to create copy and move copy into variables map
            void createVariable (const std::string& key, Variable val);
                        
        private:
            //map of string name given in JSON to a specific variable
            std::unordered_map<std::string, Variable> variables;

    };
}
