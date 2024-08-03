namespace project
{

struct Fighters_networkdata: public scriptnode::dll::InterpretedNetworkData
{
	String getId() const override
	{
		return "Fighters";
	}
	bool isModNode() const override
	{
		return false;
	}
	String getNetworkData() const override
	{
		return "581.nT6K8CVLEzcD.XiVTYB7Ni1hgbvjfYwD7lfFdpTNSD5v3FVXSTjQ1yHJbhDLpmBr8vn7GfD.KA.R.bmWbR+EhlC.jqabCW+bHWm8X7jyGG5MLo6Woyb0h4E35s77xmqMiMg.x0el0hy0ROOx0UK0hFe+7lFEBO.W+.kFtNy05I+VBXMIwxR9fOo6v8toV3onpljHsfRPOgHZqmDNIYpp5UEiwIIF7CbsmOyUCofvm0D7AkdNBYPu374KJoC.FyJO3BtCW+czLsnRq7alAHiRlrjxXkjzOHC1LmavcDgwH26F5Pa5XwIn6b8o357VgCIihlI9iOMdZ99br2KPBjwclX7nN+3mBWfm68K1ZU5V1Z2b4PfupzX7YUJdjyfMr57dg6nwUKsVsSb4W6NqXCKS8bkUmWDI6yXulGG4Zyzpshq.z8MMpD9.wFCFatyjHdrS7h9ipW0zyBFcCt7GcCSXfFVKhgJoF.oEfRB.fA.fHrjAnRFFuCyGECYVWddhpT2IEqNLYdUz.AvJK+iiOXA+Clh+fgrRCs5MxLC.TROTXsMs5bsuZNhJlK2l8XmCf4POy9EczhIfJaneE12SvHw9UBD95IZTJd3S9YPDmOi5Vf9MYLnYOYMiQYMdP6T8HpQBxXIy.YmsT.rWqQL7APx.fhCxyBFrIEKZnhgxB.yuJw4Kb.HNvalwF1ZMyjWbVQAmYaIfEAsMpMFCJ7PY.CgfZIu2sUCnnJygJdvCh.i.IPN33tijGlHRGHYwkbmWWGPOOvu.nuG";
	}
};
}

