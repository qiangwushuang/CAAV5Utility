// COPYRIGHT DASSAULT SYSTEMES 2009
//===================================================================
//
// IdentityCard.h
// Supplies the list of prerequisite components for framework SpecificationCheckFw
//
//===================================================================
//
// Usage notes:
//   For every prereq framework FW, use the syntax:
//   AddPrereqComponent ("FW", Public);
//
//===================================================================
AddPrereqComponent("System",Protected);
AddPrereqComponent("SpecialAPI",Public);
AddPrereqComponent("ApplicationFrame",Protected);
AddPrereqComponent("DialogEngine",Protected);
AddPrereqComponent("ProductStructure",Protected);
AddPrereqComponent("AdvancedMathematics",Protected);
AddPrereqComponent("MeasureGeometryInterfaces", Protected);
AddPrereqComponent("Dialog", Protected);
