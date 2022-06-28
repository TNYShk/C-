const fsPromises = require('fs').promises;
const path = require('path');

const fileOps = async () =>{
    try{
        const data = await fsPromises.readFile(path.join(__dirname,'starter.txt'), 'utf8');
        console.log(data);
        //fsPromises.unlink(path.join(__dirname,'starter.txt'));
        await fsPromises.appendFile(path.join(__dirname,'promiseWrite.txt'),'\n\n'+data);
        await fsPromises.appendFile(path.join(__dirname,'promiseWrite.txt'),'\n\n bla bla bla append');
        await fsPromises.rename(path.join(__dirname,'promiseWrite.txt'),path.join(__dirname,'newPromiseWrite.txt'));

    } catch (err){
        console.error(err);
    }
}

fileOps();

/* fs.writeFile(path.join(__dirname,'reply.txt'),'writing to file!', (err) => {
    if (err) throw err;
    console.log('write done!');

    fs.appendFile(path.join(__dirname,'reply.txt'),'\n\nappending stuff', (err) =>{
        if(err) throw err;
        console.log('append done!');

        fs.rename(path.join(__dirname,'reply.txt'),path.join(__dirname,'newReply.txt'), (err) =>{
            if(err) throw err;
            console.log('rename done!')
        })
    })
}) */

process.on('uncaughtException', err => {
    
    console.error(`Uncaught Error occured!!: Caught exception: ${err}\n`);
    process.exit(1);
})