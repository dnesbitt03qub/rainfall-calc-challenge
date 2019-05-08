const AUTHOR = 'zombeej'
const LANG = `Node ${process.version}`
const NOTES = 'Single-threaded & slow as molasses'

const fs = require('fs')
const start = Date.now()

const readStream = fs.createReadStream('../data/all.csv', 'utf8')
let lastLine = ''
let lines = 0
let stations = {}

readStream.on('data', function(chunk) {
  let data = chunk.split('\n')
  data[0] = lastLine + data[0]
  lastLine = data.splice(-1)
  data.forEach((r, i) => {
    let cols = r.split(',')
    if (cols[0] === 'StnID' || cols[1] <= 45) { return }
    let prevTime = stations[cols[0]] || 0
    let s = 6
    let time = 0
    for (s; s < 480; s = s+5) {
      if (parseInt(cols[s]) > 0) { time++ }
    }
    stations[cols[0]] = prevTime + time
  })
  lines = lines + data.length
}).on('end', () => {
  let longest = [{id: '', time: 0}]
  let longestInt = 0
  Object.keys(stations).forEach((k, i) => {
    const time = stations[k]
    if (time > longest[0].time) {
      longest = [{id: k, time}]
    } else if (time === longest[0].time) {
      longest.push({id: k, time})
    }
    longestInt = longest.reduce((agg, v) => {
      return agg + parseInt(v.id.match(/[1-9]\d*/))
    }, 0)
  })
  const end = Date.now()
  console.log(`${AUTHOR}, ${LANG}, ${longestInt}, ${end - start}, ${NOTES}`)
})