const { Worker } = require('worker_threads')

const AUTHOR = 'zombeej'
const LANG = `Node ${process.version}`
const NOTES = 'Multi-threaded'

const fs = require('fs')
const start = Date.now()

const readStream = fs.createReadStream('../data/all.csv', 'utf8')
let lastLine = ''
let lines = 0
let stations = {}

let workers = []
let buffer = []

readStream.on('data', function(chunk) {
  let data = chunk.split('\n')
  data[0] = lastLine + data[0]
  lastLine = data.splice(-1)
  data.forEach((r, i) => {
    const lat = parseFloat(r.substring(12, 19))
    if (lat <= 45) { return }
    if (buffer.length < 10000) {
      buffer.push(r)
    } else {
      workers.push(runService(buffer))
      buffer = []
    }
  })
  lines = lines + data.length
}).on('end', async () => {
  // console.log('all data streamed')
  let longest = [{id: '', time: 0}]
  let longestInt = 0
  let res = await Promise.all(workers)
    .catch(err => {
      console.error(err)
    })
  res.forEach((r, i) => {
    if (!r || !r.length) { return }
    // if (i % 10 === 0) { console.log('r', r) }
    r.forEach((n, ni) => {
      // if (i === 1 && ni === 1) { console.log('r', r) }
      let s = stations[n.station] || 0
      stations[n.station] = s + n.time
    })
  })
  // console.log(res.lengath, 'workers resolved')
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

function runService(workerData) {
  return new Promise((resolve, reject) => {
    const worker = new Worker('./worker.js', { workerData });
    worker.on('message', resolve);
    worker.on('error', reject);
    worker.on('exit', (code) => {
      if (code !== 0)
        reject(new Error(`Worker stopped with exit code ${code}`));
    })
  })
}
