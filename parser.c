void parser() {
	tk = scanner();
	//call first nonterminal
	if (tk == EOFtk)
		return ok;
	else error ("tk received, EOFtk expected");
}

