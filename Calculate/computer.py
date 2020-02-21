'''This program is used for calculating an expression.
Given an expression in input.txt, calculate the value.
For simplicity, each element of our expression is seperated by a space (for simple spliting).
Struct of our algorithm:
class Stack
function priority: priority of operation.
function inFix2postFix: convert from infix type to postfix type
function calculate: calculate the value after converting to postfix type, this is the desired value
'''
class Stack:
    '''Stack structure with push,pop,isEmpty,and get'''
    def __init__(self):
        self.__arr=[]
    def push(self,value):#push value into stack
        self.__arr.append(value)
    def pop(self):#pop the last value from stack
        returnValue=self.__arr[-1]
        self.__arr.pop()
        return returnValue
    def isEmpty(self):#Checking a stack is empty or not
        return True if len(self.__arr)==0 else False
    def get(self):#get the value at the last of stack, but not pop
        return self.__arr[-1]
def priority(character):
    '''Priority of our operation
    Here, we set:
    (:  priority=0 (lowest)
    + and -: priority=1
    * and /:priority=2(highest) 
    '''
    if(character=='('):return 0
    elif(character=='+' or character=='-'):return 1
    elif(character=='*' or character=='/'):return 2
def inFix2postFix(inFixCharacter):
    #Convert from in-fix into post-fix
    postFixCharacter=[]#the list of desired post-fix
    stack=Stack()#initialize a stack
    for character in inFixCharacter:
        '''Iter in all element in inFixCharacter
        If it is ( then push it to stack
        If it is +,-,*,/, we pop all character from stack until the priority of last is greater
        appened all the poped to post-fix list and push the character into stack
        If it is a ), the pop all character from stack until we pop a (, then append all the poped into post-fix list
        If it is a number, then append it into post-fix list
        After we iter all element in in-fix, the if stack has any elements, pop and append it to post-fix
        '''
        if(character=='('):stack.push(character)
        elif(character=='+' or character=='-' or character=='*' or character=='/'):
            while((not stack.isEmpty()) and priority(character)<=priority(stack.get())):
                value=stack.pop()
                postFixCharacter.append(value)
            stack.push(character)
        elif(character==')'):
            while(True):
                value=stack.pop()
                if(value!='('):
                    postFixCharacter.append(value)
                else:break
        else:
            postFixCharacter.append(character)
    while(not stack.isEmpty()):
        character=stack.pop()
        postFixCharacter.append(character)
    return postFixCharacter
def calculate(postFixCharacter):
    '''
    Iter in all elements in post-fix:
    If it is a number then push it into stack
    If it is + or - or * or / then pop 2 number from stack, calculate the operation between those
    numbers and push the result into stack.
    '''
    stack=Stack()
    for character in postFixCharacter:
        if(character=='+'):
            value1=stack.pop()
            value2=stack.pop()
            result=value1+value2
            stack.push(result)
        elif(character=='-'):
            value1=stack.pop()
            value2=stack.pop()
            result=value2-value1
            stack.push(result)
        elif(character=='*'):
            value1=stack.pop()
            value2=stack.pop()
            result=value1*value2
            stack.push(result)
        elif(character=='/'):
            value1=stack.pop()
            value2=stack.pop()
            result=value2/value1
            stack.push(result)
        else: stack.push(float(character))
    return stack.pop()
if(__name__=='__main__'):
    err_flag=False #Error flag =True if an exception has occurred
    try:
        fileOpen=open('input.txt','r')
        myStr=fileOpen.readline()
    except Exception as emsg:
        print("Error")
        print(emsg)
        err_flag=True
    if(not err_flag):
        inFixCharacter=myStr.split()
        postFixCharacter=inFix2postFix(inFixCharacter)
        print(calculate(postFixCharacter))