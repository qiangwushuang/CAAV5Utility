// COPYRIGHT DASSAULT SYSTEMES 2009
//===================================================================
//
// IdentityCard.h
// Supplies the list of prerequisite components for framework CommonFw
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
AddPrereqComponent("ObjectModelerBase",Public);
AddPrereqComponent("Visualization",Public);
AddPrereqComponent("ProductStructure",Public);
AddPrereqComponent("ApplicationFrame",Public);
AddPrereqComponent("InteractiveInterfaces",Public);
AddPrereqComponent("MecModInterfaces",Public);
AddPrereqComponent("MechanicalModeler",Public);
AddPrereqComponent("CommonFw",Public);