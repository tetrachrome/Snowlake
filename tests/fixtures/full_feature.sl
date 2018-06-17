group MyGroup {
  ClassName                      : MyInference;
  TypeClass                      : TypeCls;
  ProofMethod                    : proveType;
  TypeCmpMethod                  : cmpType;
  TypeAnnotationSetupMethod      : typeAnnotationSetup;
  TypeAnnotationTeardownMethod   : typeAnnotationTeardown;
  
  inference MethodStaticDispatch {
  
    globals: [
      SELF_TYPE,
      CLS_TYPE
    ]
    
    arguments: [
      StaticMethodCallStmt : ASTExpr
    ]
    
    premises: [
      StaticMethodCallStmt.argument_types            : ArgumentsTypes[];
      StaticMethodCallStmt.callee.parameter_types    : ParameterTypes[];
      ArgumentsTypes[] <= ParameterTypes[] inrange 0..1..ParameterTypes[];
      ArgumentsTypes[0] != SELF_TYPE;
      StaticMethodCallStmt.caller_type : CLS_TYPE while {
        ArgumentsTypes[] <= ParameterTypes[] inrange 1..1..ParameterTypes[];
      };
    ]
    
    proposition : lub(T1, T2);
  }
  
  inference BinaryExpressionInference {
    
    arguments: [
      expr : Expr
    ]
    
    premises: [
      expr.lhs   : Expr;
      expr.rhs   : Expr;
    ]
    
    proposition  : Expr;
  }
}
