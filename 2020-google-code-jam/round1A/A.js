let input = '';

// idea : consider each pattern , split each into leftside + * + mid side + * + right side
// check if each right side / left side matches
// then concat mid side


process.stdin.on('data', function (data) {
  input += data;
});

process.stdin.on('end', function (data) {
  let lines = input.split('\n');
  for (let i = 0; i < lines.length; i++) lines[i] = lines[i].trim();
  let t = parseInt(lines[0]);
  let at = 1;
  for (let t = 1; t <= t; t++) {
    process.stdout.write('Case #' + t + ': ');
    let n = parseInt(lines[at++]);
    let strs = [];
    for (let i = 0; i < n; i++) {
      strs.push(lines[at++]);
    }
    let regexes = strs.map(s => new RegExp('^' + s.replace(/\*/g, '.*') + '$', 'i'));
    function check(potential) {
      for (let r of regexes) {
        if (potential.match(r) == null) return false;
      }
      return true;
    }
    let no_asterisk = strs.filter(s => s.match(/\*/g) === null);
    if (no_asterisk.length !== 0) {
      if (check(no_asterisk[0])) {
        process.stdout.write(no_asterisk[0] + '\n');
      } else {
        process.stdout.write('*\n');
      }
    } else {
      let leftside = [];
      let rightside = [];
      let midpart = [];
      for (let i = 0; i < n; i++) {
        leftside.push(strs[i].match(/^[A-Z]*\*/g)[0]);
        rightside.push(strs[i].match(/\*[A-Z]*$/g)[0]);
        leftside[i] = leftside[i].substr(0, leftside[i].length - 1);
        rightside[i] = rightside[i].substr(1);
        midpart.push(strs[i].substr(leftside[i].length, strs[i].length-leftside[i].length-rightside[i].length));
      }
      let l = '';
      let r = '';
      let m = midpart.map(m => m.replace(/\*/g, '')).join('');
      for (let i = 0; i < n; i++) {
        if (leftside[i].length > l.length) l = leftside[i];
        if (rightside[i].length > r.length) r = rightside[i];
      }
      let ans = l + m + r;
      if (check(ans)) {
        process.stdout.write(ans + '\n');
      } else {
        process.stdout.write('*\n');
      }
    }
  }
});
