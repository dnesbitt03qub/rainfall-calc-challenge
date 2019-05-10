const { workerData, parentPort } = require('worker_threads')

// console.log('\n\nworkerThread')
let data = []
workerData.forEach(r => {
  let cols = r.split(',')
  if (cols[0] === 'StnID' || cols[1] <= 45) {
    parentPort.postMessage('')
    return
  }
  // let prevTime = stations[cols[0]] || 0
  let s = 6
  let time = 0
  for (s; s < 480; s = s+5) {
    if (parseInt(cols[s]) > 0) { time++ }
  }
  data.push({
    station: cols[0],
    time
  })
})
parentPort.postMessage(data)
