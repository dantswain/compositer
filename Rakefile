require 'rake/clean'

CLEAN.include('*.o')
CLOBBER.include('test_BelugaIPCClient')

INC_DIR = "../src"

task :default => ["Compositer"]

CV_C_FLAGS = %x[pkg-config opencv --cflags].strip
CV_LIBS = %x[pkg-config opencv --libs].strip

rule '.o' => '.cpp' do |t|
  sh "g++ -I#{INC_DIR} #{CV_C_FLAGS} -c #{t.source}"
end

task "Compositer" => ['src/Compositer.o'] do |t|
  objs = t.prerequisites.map{|p| p.pathmap("%f")}.join(' ')
  sh "g++ -o #{t.name} #{objs} #{CV_LIBS}"
end
