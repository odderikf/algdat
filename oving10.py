import re
i = re.compile(r".*\d.*", re.DOTALL)
ii = re.compile(r"\d\d/\d\d/\d\d\d\d")
ii_a = re.compile(r"([012][0-9])|(3[01])/((0[0-9])|(1[012]))/[12]\d\d\d")
iii = re.compile(r".{10,}", re.DOTALL)
iv = re.compile(r".*(\W|[0-9])+.*", re.DOTALL)
