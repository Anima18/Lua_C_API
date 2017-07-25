--package.path = "E:\\code\\c_workspace\\Lua_C_API\\src\\lua\\?.lua"
--package.cpath = "E:\\code\\c_workspace\\Lua_C_API\\bin\\Debug\\?.dll"
--require ("mytestlib")
--mytestlib = package.loadlib("mytestlib.dll","luaopen_mytestlib");
--print(mytestlib);
--mytestlib();

function testCFunction()
	print("testCFunction");

	result = mytestlib.add(1.0,2.0);

	print(mytestlib.add(1.0,2.0));
	print(mytestlib.sub(20.1,19));

	return result;

end


